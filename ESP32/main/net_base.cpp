#include "net_base.h"

//#include "sdkconfig.h"
//#include "driver/gpio.h"
//#include "esp_vfs_semihost.h"
//#include "esp_vfs_fat.h"
//#include "esp_spiffs.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"
//#include "esp_log.h"
//#include "mdns.h"
//#include "lwip/apps/netbiosns.h"
#include "protocol_examples_common.h"

// -------------------------------------------------------------------------------
void netBaseInit () {
  ESP_ERROR_CHECK(nvs_flash_init());
  ESP_ERROR_CHECK(esp_netif_init());
  ESP_ERROR_CHECK(esp_event_loop_create_default());

  ESP_ERROR_CHECK(example_connect());
}
