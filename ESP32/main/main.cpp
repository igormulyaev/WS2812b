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
#include "effects/led_effect.h"
#include "effects/stars.h"
#include "effects/christmas_tree.h"
#include "effects/fire_effect.h"
#include "effects/test_effect.h"

#include "led_event_loop.h"

#include "FastLED.h"
#include "FX.h"

extern "C" {
  void app_main();
}

// -------------------------------------------------------------------------------
void app_main() {
  ledBaseInit ();

  CLedEffectLoop ledEffectLoop;
  CTestEffect testEffect;

  ledEffectLoop.postStartEvent(&testEffect);

  char c;

  // loop task
  while (true) {
    c = 'R';
    ledEffectLoop.postInteractEvent(&c, sizeof(c));
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    c = 'G';
    ledEffectLoop.postInteractEvent(&c, sizeof(c));
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    c = 'B';
    ledEffectLoop.postInteractEvent(&c, sizeof(c));
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    c = 'x';
    ledEffectLoop.postInteractEvent(&c, sizeof(c));
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  };
}
