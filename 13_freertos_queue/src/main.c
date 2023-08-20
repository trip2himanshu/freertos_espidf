/*
device: esp32s3 devkitc-1
platform: espidf
author: himanshu tripathi
description: queue in freertos
*/

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <stdio.h>

// handle for tasks
TaskHandle_t task_send_handle = NULL;
TaskHandle_t task_recv_handle = NULL;
// queue handle
QueueHandle_t queue;

// Task 1
// Task to send
void task_send() {
  char str_send[9];
  sprintf(str_send, "data 1");
  xQueueSend(queue, (void *)str_send, pdMS_TO_TICKS(100));
  printf("Send: %s \n", str_send);
  sprintf(str_send, "data 2");
  xQueueSend(queue, (void *)str_send, pdMS_TO_TICKS(100));
  printf("Send: %s \n", str_send);
  sprintf(str_send, "data 3");
  xQueueSend(queue, (void *)str_send, pdMS_TO_TICKS(100));
  printf("Send: %s \n", str_send);
  while (1) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// Task 2
// Task to receive
void task_recv() {
  char str_recv[9];
  while (1) {
    if (xQueueReceive(queue, &(str_recv), pdMS_TO_TICKS(100))) {
      printf("Received: %s \n", str_recv);
    }
  }
}

void app_main() {
  // queue creation
  queue = xQueueCreate(5, 10);
  // available
  printf("\nAvailable at the begining: %d \n", uxQueueSpacesAvailable(queue));

  // write data to queue
  xTaskCreate(task_send, "Task Send", 4096, NULL, 1, &task_recv_handle);
  vTaskDelay(pdMS_TO_TICKS(1000));
  xTaskCreate(task_recv, "Task Recv", 4096, NULL, 2, &task_recv_handle);
  vTaskDelay(pdMS_TO_TICKS(1000));

  printf("\nAvailable at the end: %d\n", uxQueueSpacesAvailable(queue));
}