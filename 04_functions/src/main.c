/*
device: esp32s3 devkitc-1
platform: espidf
author: hiamnshu tripathi
description: handling functions in freertos and espidf
*/

#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

// function 1
void vfunction1() {
  for (size_t i = 0; i < 5; i++) {
    printf("Function 1 %d : %lld\n", i, esp_timer_get_time() / 1000);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// function 2
void vfunction2() {
  for (size_t i = 0; i < 5; i++) {
    printf("Function 1 %d : %lld\n", i, esp_timer_get_time() / 1000);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void app_main() {
  printf("program starts at: %lld\n", esp_timer_get_time() / 1000);
  vfunction1();
  printf("\n");
  vfunction2();
  printf("program ends at: %lld\n", esp_timer_get_time() / 1000);
}