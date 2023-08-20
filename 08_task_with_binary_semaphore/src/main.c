/*
device: esp32s3 devkitc-1
platform: espidf
author: himanshu tripathi
description: task with binary semaphore
*/

#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <stdio.h>

// configure freertos to run tasks in one core only
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// handle for semaphore
SemaphoreHandle_t xSemaphore = NULL;

// Task 1
void vTask1() {
  for (size_t i = 0; i < 5; i++) {
    printf("Task %d : %lld\n", i, esp_timer_get_time() / 1000);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  xSemaphoreGive(xSemaphore);
  vTaskDelete(NULL);
}

void app_main() {
  xSemaphore = xSemaphoreCreateBinary();
  printf("\nTimer output in milliseconds program initiation: %lld\n",
         esp_timer_get_time() / 1000);
  xTaskCreatePinnedToCore(vTask1, "Task 1", 2048, NULL, 2, NULL, app_cpu);
  //   one way of using semaphore (logically understandable)
  //   if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) {
  //     printf("\nProgram completion : %lld\n", esp_timer_get_time() / 1000);
  //   }
  // other way of using semaphore (more practcal way)
  xSemaphoreTake(xSemaphore, portMAX_DELAY);
  printf("\nProgram completion : %lld\n", esp_timer_get_time() / 1000);
}