/*
device: esp32s3 devkitc-1
platform: espidf
author: himanshu tripathi
description: handling 3 tasks using mutex semaphore
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
// print time using timer
void vTask1() {
  xSemaphoreTake(xSemaphore, portMAX_DELAY);
  for (size_t i = 0; i < 3; i++) {
    printf("Task1 %d : %lld\n", i, esp_timer_get_time() / 1000);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  printf("\n");
  xSemaphoreGive(xSemaphore);
  vTaskDelete(NULL);
}

// Task 2
// print time using timer
void vTask2() {
  xSemaphoreTake(xSemaphore, portMAX_DELAY);
  for (size_t i = 0; i < 3; i++) {
    printf("Task2 %d : %lld\n", i, esp_timer_get_time() / 1000);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  printf("\n");
  xSemaphoreGive(xSemaphore);
  vTaskDelete(NULL);
}

// Task 3
// print time using timer
void vTask3() {
  xSemaphoreTake(xSemaphore, portMAX_DELAY);
  for (size_t i = 0; i < 3; i++) {
    printf("Task3 %d : %lld\n", i, esp_timer_get_time() / 1000);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  printf("\n");
  xSemaphoreGive(xSemaphore);
  vTaskDelete(NULL);
}

void app_main() {
  xSemaphore = xSemaphoreCreateMutex();
  printf("\n");
  // create and run tasks
  xTaskCreatePinnedToCore(vTask1, "Task1", 2048, NULL, 2, NULL, app_cpu);
  xTaskCreatePinnedToCore(vTask2, "Task2", 2048, NULL, 2, NULL, app_cpu);
  xTaskCreatePinnedToCore(vTask3, "Task3", 2048, NULL, 2, NULL, app_cpu);
}