/* 
   This code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "led_base.h"
#include "net_base.h"


extern "C" {
  void app_main ();
}

// -------------------------------------------------------------------------------
void app_main () 
{
  ledBaseInit ();

  netBaseInit ();

  // loop task
  while (true) {
    vTaskDelay (1000 / portTICK_PERIOD_MS);
  };
}
