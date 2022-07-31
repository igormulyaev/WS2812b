/* 
   This code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "led_base.h"
#include "net_base.h"
#include "button_base.h"

#include "led_event_loop.h"

#include "effects/led_effect.h"
#include "effects/christmas_tree_effect.h"
#include "effects/stars_effect.h"
#include "effects/debug_effect.h"

#include "esp_log.h"

extern "C" {
  void app_main ();
}

static const char * const TAG = "main";

// -------------------------------------------------------------------------------
void app_main () 
{
  ledBaseInit ();

  buttonBaseInit ();

  ESP_LOGI (TAG, "Start debugEffect");
  ledEventLoop -> postStartEvent (debugEffect);

  ESP_LOGI (TAG, "Start key scan");

  while (gpio_get_level (GPIO_NUM_0) != 0) {
    vTaskDelay (50 / portTICK_PERIOD_MS);
  }
  netBaseInit ();

}
