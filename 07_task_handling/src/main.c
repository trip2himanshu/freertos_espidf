/*
device: esp32s3 devkitc-1
platform: espidf
author: himanshu tripathi
description: handling tasks in freertos such as
resume task, suspend task and delete task using task handle
*/

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <stdio.h>
#include <string.h>

/*configure freertos to run tasks in core 1 only*/
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

// globals
static const char sample_str[] = "This is the sample string to print";

// task handles
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

/*
Task 1
function to print one sample string on serial monitor
*/
void print_string() {
  int str_len = strlen(sample_str);
  while (1) {
    for (int16_t i = 0; i < str_len; i++) {
      //   char c = sample_str[i];
      printf("%c", sample_str[i]);
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    printf("\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

/*
Task 2
function to print * on serial monitor
*/
void print_star() {
  while (1) {
    printf("*");
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void app_main() {
  printf("Example for task handling\n");
  printf("main task is running on core %d with task priority %d\n",
         xPortGetCoreID(), uxTaskPriorityGet(NULL));

  // create and run tasks
  xTaskCreatePinnedToCore(print_string, "String Print", 1024, NULL, 1, &task_1,
                          app_cpu);
  xTaskCreatePinnedToCore(print_star, "star print", 1024, NULL, 2, &task_2,
                          app_cpu);
  while (1) {
    // suspend and resume the high priority task for some interval
    for (size_t i = 0; i < 5; i++) {
      vTaskSuspend(task_2);
      vTaskDelay(4000 / portTICK_PERIOD_MS);
      vTaskResume(task_2);
      vTaskDelay(4000 / portTICK_PERIOD_MS);
    }
    // delete the low priority task
    if (task_1 != NULL) {
      vTaskDelete(task_1);
      task_1 = NULL;
    }
  }
}