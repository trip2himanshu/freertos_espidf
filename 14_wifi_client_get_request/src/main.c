
#include <esp_http_client.h>
#include <esp_netif.h>
#include <esp_wifi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <nvs_flash.h>
#include <stdio.h>

static void wifi_event_handler(void *event_handler_arg,
                               esp_event_base_t event_base, int32_t event_id,
                               void *event_data) {
  switch (event_id) {
  case WIFI_EVENT_STA_START:
    printf("Wifi connecting ...\n");
    break;
  case WIFI_EVENT_STA_CONNECTED:
    printf("wifi connected ...\n");
    break;
  case WIFI_EVENT_STA_DISCONNECTED:
    printf("wifi lost connection ...\n");
    break;
  case IP_EVENT_STA_GOT_IP:
    printf("wifi got IP ...\n");
    break;
  default:
    break;
  }
}

esp_err_t client_event_handler(esp_http_client_event_handle_t evt) {
  switch (evt->event_id) {
  case HTTP_EVENT_ON_DATA:
    printf("HTTP_EVENT_ON_DaTA: %.*s\n", evt->data_len, (char *)evt->data);
    break;
  default:
    break;
  }
  return ESP_OK;
}

void get_rest_function() {
  esp_http_client_config_t client_configuration = {
      .url = "http://worldclockapi.com/api/json/utc/now",
      .event_handler = client_event_handler};
  esp_http_client_handle_t client = esp_http_client_init(&client_configuration);
  esp_http_client_perform(client);
  esp_http_client_cleanup(client);
}

void app_main() {
  nvs_flash_init(); // non-volatile storage
  // 1 - Wi-Fi/LwIP Init Phase
  esp_netif_init();                    // TCP/IP initiation s1.1
  esp_event_loop_create_default();     // event loop s1.2
  esp_netif_create_default_wifi_sta(); // wifi station s1.3
  wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();
  esp_wifi_init(&wifi_initiation); // s1.4

  //   2 - Wi-Fi Configuration Phase
  esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler,
                             NULL);
  esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler,
                             NULL);
  wifi_config_t wifi_configuration = {.sta = {.ssid = SSID;
  .password = PASSWORD;
}
}
;
esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration);
// 3 - Wi-Fi Start Phase
esp_wifi_start();
// 4 - Wi-Fi Connect Phase
esp_wifi_connect();
// REST get data
vTaskDelay(5000 / portTICK_PERIOD_MS);
get_rest_function();
}
