/*
device: esp32s3 devkitc-1
platform: espidf
author: himanshu tripathi
description: print the logs with espidf
*/

#include <esp_log.h>
#include <stdio.h>

#define TAG "MY TAG"

void app_main() {
  printf("printing the log info\n");
  ESP_LOGI(TAG, "Message for log");
}
