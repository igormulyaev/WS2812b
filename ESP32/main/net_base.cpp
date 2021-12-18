#include "net_base.h"

#include "esp_spiffs.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_log.h"
#include "mdns.h"
#include "protocol_examples_common.h"
#include "http_server.h"

#define MDNS_HOST_NAME "ws-esp"
#define MDNS_INSTANCE "esp home web server"
#define WEB_MOUNT_POINT "/www"

static const char* TAG = "net_base";

HttpServer* httpServer = NULL;

// -------------------------------------------------------------------------------
void initMdns() {
  mdns_init ();
  mdns_hostname_set (MDNS_HOST_NAME);
  mdns_instance_name_set (MDNS_INSTANCE);

  ESP_ERROR_CHECK (mdns_service_add ("ESP32-WebServer", "_http", "_tcp", 80, NULL, 0));
}

// -------------------------------------------------------------------------------
esp_err_t initFs () {
  esp_vfs_spiffs_conf_t conf = {
    .base_path = WEB_MOUNT_POINT,
    .partition_label = NULL,
    .max_files = 5,
    .format_if_mount_failed = false
  };

  esp_err_t ret = esp_vfs_spiffs_register (&conf);

  if (ret != ESP_OK) {
    if (ret == ESP_FAIL) {
      ESP_LOGE (TAG, "Failed to mount or format filesystem");
    } else if (ret == ESP_ERR_NOT_FOUND) {
      ESP_LOGE (TAG, "Failed to find SPIFFS partition");
    } else {
      ESP_LOGE (TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name (ret));
    }
    return ESP_FAIL;
  }

  size_t total = 0, used = 0;
  ret = esp_spiffs_info (NULL, &total, &used);

  if (ret != ESP_OK) {
    ESP_LOGE (TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name (ret));
  } else {
    ESP_LOGI (TAG, "Partition size: total: %d, used: %d", total, used);
  }
  return ESP_OK;
}

// -------------------------------------------------------------------------------
void netBaseInit () {
  ESP_ERROR_CHECK (nvs_flash_init ());
  ESP_ERROR_CHECK (esp_netif_init ());
  ESP_ERROR_CHECK (esp_event_loop_create_default ());

  httpServer = new HttpServer;

  initMdns ();

  ESP_ERROR_CHECK (example_connect ());
  ESP_ERROR_CHECK (initFs ());

  ESP_ERROR_CHECK (httpServer -> startServer (WEB_MOUNT_POINT));
}
