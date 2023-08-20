/*
device: esp32s3 devkitc-1
platform: espidf
author: himanshu tripathi
description:
step 1: write main.c file without the string inputs, build and run it
it will show the SSID and PASSWORD on serial monitor
step 2: create a new file inside src folder with name Kconfig.projbuild
define menu and default string value inside Kconfig file
update the main.c file with string values
clean the project and rebuild project
step 3: update the SSID and PASSWORD values from menuconfig
run menuconfig and update the values
rebuild the project and run
*/

#include <sdkconfig.h>
#include <stdio.h>

void app_main() {
  // print the saved and updated values of SSID and PASSWORD
  printf("SSID: %s\n", CONFIG_SSID);
  printf("PASSWORD: %s\n", CONFIG_PASSWORD);
}