/*
device: esp32s3 devkitc-1
platform: espidf
author: himanshu tripathi
description: creating two tasks in freertos and espidf
*/

#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

#if CONFIGURE_FREERTOS_UNICORE
BaseType_t app_cpu = 0;
#else
BaseType_t app_cpu = 1;
#endif

// function for task 1
void task1() {
  while (1) {
    for (size_t i = 0; i < 5; i++) {
      printf("Task 1>> %d : %lld\n", i, esp_timer_get_time() / 1000);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("\n");
  }
}

// function for task 2
void task2() {
  while (1) {
    for (size_t i = 0; i < 5; i++) {
      printf("Task 2>> %d : %lld\n", i, esp_timer_get_time() / 1000);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("\n");
  }
}

void app_main() {
  printf("Program starts at %lld\n", esp_timer_get_time() / 1000);
  // create and run tasks
  xTaskCreatePinnedToCore(task1, "Task 1", 2048, NULL, 1, NULL, app_cpu);
  xTaskCreatePinnedToCore(task2, "Task 2", 2048, NULL, 1, NULL, app_cpu);
  printf("Program ends at %lld\n", esp_timer_get_time() / 1000);
}