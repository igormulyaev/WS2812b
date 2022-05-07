#include "button_base.h"

#include "esp_log.h"
#include "driver/gpio.h"

#define GPIO_INPUT_PIN_SEL  (1ULL<<GPIO_INPUT_IO_0)

static const char* TAG = "button_base";

// -------------------------------------------------------------------------------
void buttonBaseInit () 
{
  ESP_LOGI (TAG, "Start init button GPIO");

  gpio_config_t button_conf = {
    .pin_bit_mask = GPIO_INPUT_PIN_SEL,
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLUP_ENABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .intr_type = GPIO_INTR_DISABLE
  };

  ESP_ERROR_CHECK (gpio_config (&button_conf));

  ESP_LOGI (TAG, "End init button GPIO");
}
