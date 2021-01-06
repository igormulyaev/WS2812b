/* 
   This code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "led_params.h"
#include "stars.h"
#include "christmas_tree.h"

#include "FastLED.h"
#include "FX.h"

#define GPIO_INPUT_IO_0     GPIO_NUM_0
#define GPIO_INPUT_PIN_SEL  (1ULL<<GPIO_INPUT_IO_0)
#define ESP_INTR_FLAG_DEFAULT 0

extern "C" {
  void app_main();
}

CRGB leds[NUM_LEDS];

void app_main() {

  printf(" entering app main, call add leds\n");
  // the WS2811 family uses the RMT driver
  FastLED.addLeds<LED_TYPE, LED_DATA_PIN>(leds, NUM_LEDS);

  FastLED.clearData();
  FastLED.show();

  // all leds test 6 times
  for (int tst = 0; tst < 6; ++tst) {
    CRGB color;
    switch (tst % 3) {
      case 0:
        color = 0x040000;
        printf("test green\n");
        break;
      case 1:
        color = 0x000400;
        printf("test red\n");
        break;
      case 2:
        color = 0x000004;
        printf("test blue\n");
        break;
    }
    FastLED.showColor(color);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  /*
  printf("Start Stars task\n");

  xTaskCreatePinnedToCore(&starsStart, "stars", 4000, NULL, 5, NULL, 0);
  */
  printf("Start Christmas Tree task\n");

  xTaskCreatePinnedToCore(&treeStart, "tree", 4000, NULL, 5, NULL, 0);
}
