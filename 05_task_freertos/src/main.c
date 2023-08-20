/*
device: esp32s3 devkitc-1
platform: espidf
author: hiamnshu tripathi
description: creating and running task in freertos and espidf
*/

#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

#if CONFIG_FREERTOS_UNICORE
BaseType_t app_cpu = 0;
#else
BaseType_t app_cpu = 1;
#endif
// function for task
void task_1() {
  while (1) {
    for (size_t i = 0; i < 5; i++) {
      printf("Function 1 %d : %lld\n", i, esp_timer_get_time() / 1000);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("\n");
  }
}

void app_main() {
  printf("program starts at: %lld\n", esp_timer_get_time() / 1000);

  xTaskCreatePinnedToCore(task_1,   // function to be called
                          "task 1", // task name
                          2048,     // task stack size
                          NULL,     // parameters pass to function
                          1,        // task priority
                          NULL,     // task handle
                          app_cpu); // run task in core 1

  vTaskDelay(2000 / portTICK_PERIOD_MS);
  printf("program ends at: %lld\n", esp_timer_get_time() / 1000);
}