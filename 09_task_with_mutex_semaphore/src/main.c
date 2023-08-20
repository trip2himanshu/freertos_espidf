/*
device: esp32s3 devkitc-1
platform: espidf
author: himanshu tripathi
description: task with mutex semaphore
Binary Semaphore: when ever the semaphore is given or taken
binary semaphore status changes between 0 and 1
Mutex Semaphore: it requires the give and take statements in pair
*/

#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <stdio.h>

// configure device to run tasks in one core only
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// handle for semaphore
SemaphoreHandle_t xSemaphore = NULL;

// Task 1
void vTask1() {
  // starting of task takes the semaphore
  xSemaphoreTake(xSemaphore, portMAX_DELAY);
  for (size_t i = 0; i < 5; i++) {
    printf("\nTask %d : %lld\n", i, esp_timer_get_time() / 1000);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  //   after finishing the task it give the semaphore
  xSemaphoreGive(xSemaphore);
  vTaskDelete(NULL);
}
void app_main() {
  xSemaphore = xSemaphoreCreateMutex();
  printf("\nProgram starts at : %lld\n", esp_timer_get_time() / 1000);
  // create and run the task
  xTaskCreatePinnedToCore(vTask1, "Task1", 2048, NULL, 2, NULL, app_cpu);
  //   give delay so that task mey get started before the execution of next
  //   statement
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  //   main function takes the semaphore
  xSemaphoreTake(xSemaphore, portMAX_DELAY);
  printf("\nProgram ends at : %lld\n", esp_timer_get_time() / 1000);
  //   main function give the semaphore
  xSemaphoreGive(xSemaphore);
}