#include "led_base.h"
#include "effects/test_effect.h"
#include "effects/christmas_tree_effect.h"
#include "effects/stars_effect.h"
#include "effects/debug_effect.h"
#include "led_event_loop.h"
#include "rmt_led.h"
#include <cstring>
#include "esp_log.h"

static const char* const TAG = "led_base";

// ########################################################
// ### Led buffer
// ########################################################
RGB leds[LED_COUNT];

// ########################################################
// ### Led buffer clean
// ########################################################
void ledsClean () 
{
  memset (static_cast <void*> (leds), 0, sizeof(leds));
}

// ########################################################
// ### Led buffer set color
// ########################################################
void ledsSet (RGB color)
{
  RGB* p = leds;
  for (int i = LED_COUNT; i; --i) {
    *p++ = color;
  }
}

// ########################################################
// ### Led initialization
// ########################################################
void ledBaseInit () {
  ESP_LOGI (TAG, "Start init LED");
  ledsClean ();

  rmtLed = new RmtLed;
  ledEventLoop = new LedEventLoop;

  testEffect = new TestEffect;
  christmasTreeEffect = new ChristmasTreeEffect;
  starsEffect = new StarsEffect;
  debugEffect = new DebugEffect;

  ESP_LOGI (TAG, "End init LED");
}

// ########################################################
// ### Pointers to classes instances
// ########################################################

RmtLed* rmtLed = NULL;
LedEventLoop* ledEventLoop = NULL;

TestEffect* testEffect = NULL;
ChristmasTreeEffect* christmasTreeEffect = NULL;
StarsEffect* starsEffect = NULL;
DebugEffect* debugEffect = NULL;

