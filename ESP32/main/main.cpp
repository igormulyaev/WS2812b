#include "led/led_base.h"
#include "net_base.h"
#include "button_base.h"

#include "led/led_event_loop.h"
#include "director.h"

#include "esp_log.h"

extern "C" {
  void app_main ();
}

static const char * const TAG = "main";

// -------------------------------------------------------------------------------
void app_main () 
{
  ledBaseInit ();

  director = new Director;

  buttonBaseInit ();

  netBaseInit ();

}
