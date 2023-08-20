/*
device: esp32s3 devkitc-1
platform: espidf
author: himanshu tripathi
description: read serial data from serial port without using uart
using printf() and scanf()
*/

#include "driver/uart.h"
#include <stdio.h>
#include <string.h>

void app_main() {
  char c[10];
  while (1) {
    printf("\nEnter data: ");
    scanf("%9s", c);
    printf("\ndata entered: %s\n", c);
    strcpy(c, "");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}