/* 
   This code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "led_base.h"
#include "net_base.h"

#include "led_event_loop.h"
#include "effects/test_effect.h"

extern "C" {
  void app_main ();
}

// -------------------------------------------------------------------------------
void app_main () {
  ledBaseInit ();

  netBaseInit ();

  CTestEffect testEffect;

  ledEventLoop -> postStartEvent (&testEffect);

  char c;

  // loop task
  while (true) {
    c = 'R';
    ledEventLoop -> postInteractEvent (&c, sizeof (c));
    vTaskDelay (1000 / portTICK_PERIOD_MS);

    c = 'G';
    ledEventLoop -> postInteractEvent (&c, sizeof(c));
    vTaskDelay (1000 / portTICK_PERIOD_MS);

    c = 'B';
    ledEventLoop -> postInteractEvent (&c, sizeof(c));
    vTaskDelay (1000 / portTICK_PERIOD_MS);

    c = 'x';
    ledEventLoop -> postInteractEvent (&c, sizeof(c));
    vTaskDelay (1000 / portTICK_PERIOD_MS);
  };
}
