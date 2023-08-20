/*
device: esp32s3 devkitc-1
platform: espidf
author: himanshu tripathi
description: comparison of timers in espidf
*/

#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <stdio.h>

void app_main() {
  // portTICK_PERIOD_MS
  printf("timer milliseconds 1:\n");
  printf("Timer: %lld milliseconds\n", esp_timer_get_time() / 1000);
  vTaskDelay(1 / portTICK_PERIOD_MS);
  printf("Timer: %lld milliseconds\n", esp_timer_get_time() / 1000);
  printf("timer milliseconds 10:\n");
  printf("Timer: %lld milliseconds\n", esp_timer_get_time() / 1000);
  vTaskDelay(10 / portTICK_PERIOD_MS);
  printf("Timer: %lld milliseconds\n", esp_timer_get_time() / 1000);
  printf("timer milliseconds 100:\n");
  printf("Timer: %lld milliseconds\n", esp_timer_get_time() / 1000);
  vTaskDelay(100 / portTICK_PERIOD_MS);
  printf("Timer: %lld milliseconds\n", esp_timer_get_time() / 1000);
  printf("timer milliseconds 1000:\n");
  printf("Timer: %lld milliseconds\n", esp_timer_get_time() / 1000);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  printf("Timer: %lld milliseconds\n", esp_timer_get_time() / 1000);

  // pdMS_TO_TICKS
  printf("timer milliseconds 1:\n");
  printf("Timer: %lld milliseconds\n", esp_timer_get_time() / 1000);
  vTaskDelay(pdMS_TO_TICKS(1));
  printf("Timer: %lld milliseconds\n", esp_timer_get_time() / 1000);
  printf("timer milliseconds 10:\n");
  printf("Timer: %lld milliseconds\n", esp_timer_get_time() / 1000);
  vTaskDelay(pdMS_TO_TICKS(10));
  printf("Timer: %lld milliseconds\n", esp_timer_get_time() / 1000);
  printf("timer milliseconds 100:\n");
  printf("Timer: %lld milliseconds\n", esp_timer_get_time() / 1000);
  vTaskDelay(pdMS_TO_TICKS(100));
  printf("Timer: %lld milliseconds\n", esp_timer_get_time() / 1000);
  printf("timer milliseconds 1000:\n");
  printf("Timer: %lld milliseconds\n", esp_timer_get_time() / 1000);
  vTaskDelay(pdMS_TO_TICKS(1000));
  printf("Timer: %lld milliseconds\n", esp_timer_get_time() / 1000);
}