/* 
   This code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "led_base.h"
#include "net_base.h"

#include "led_event_loop.h"

#include "effects/led_effect.h"
#include "effects/christmas_tree_effect.h"
#include "effects/stars_effect.h"

#include "esp_log.h"

extern "C" {
  void app_main ();
}

static const char * const TAG = "main";

// -------------------------------------------------------------------------------
void app_main () 
{
  ledBaseInit ();

/*  ledEventLoop -> startEventAction (&christmasTreeEffect);

  while (true) {
    vTaskDelay (1000 / portTICK_PERIOD_MS);
  };
*/
  while (true) {
    ESP_LOGI (TAG, "Start christmasTreeEffect");
    ledEventLoop -> postStartEvent (christmasTreeEffect);

    vTaskDelay (60 * 1000 / portTICK_PERIOD_MS);

    ESP_LOGI (TAG, "Start starsEffect");
    ledEventLoop -> postStartEvent (starsEffect);

    vTaskDelay (60 * 1000 / portTICK_PERIOD_MS);
  }

  netBaseInit ();

  // loop task
  while (true) {
    vTaskDelay (1000 / portTICK_PERIOD_MS);
  };
}
