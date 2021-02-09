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
#include "led_effect.h"

#include "FastLED.h"
#include "FX.h"

#define GPIO_INPUT_IO_0     GPIO_NUM_0
#define GPIO_INPUT_PIN_SEL  (1ULL<<GPIO_INPUT_IO_0)
#define ESP_INTR_FLAG_DEFAULT 0

extern "C" {
  void app_main();
}

CRGB leds[NUM_LEDS];

esp_timer_handle_t ledRefreshTimerH;

CLedEffect *currentEffect;

// -------------------------------------------------------------------------------
// all leds test 6 times
void testLeds() {
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
}


//--------------------------------------------------------
static void ledRefreshCallback (void *param) {
  currentEffect -> OnTimer();
};

// -------------------------------------------------------------------------------
void startLedRefresh() {

  esp_timer_create_args_t timer_create_args = {
      .callback = ledRefreshCallback,
      .arg = NULL,
      .dispatch_method = ESP_TIMER_TASK,
      .name = "Led_refresh_timer"
  };

  esp_timer_create(&timer_create_args, &ledRefreshTimerH);

  esp_timer_start_periodic(ledRefreshTimerH, 1000000L / LED_FPS);
}

// -------------------------------------------------------------------------------
void app_main() {

  printf("entering app main, call add leds\n");

  FastLED.addLeds<LED_TYPE, LED_DATA_PIN>(leds, NUM_LEDS);

  FastLED.clearData();
  FastLED.show();

  printf("run test\n");
  testLeds();

  printf("create tree\n");
  //currentEffect = new CChristmasTree;
  currentEffect = new CStars;
  currentEffect -> OnStart();

  printf("run refresh timer\n");
  startLedRefresh();

  // loop task
  while (true) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  };
}
