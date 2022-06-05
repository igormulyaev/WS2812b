#include "led_base.h"
#include "effects/test_effect.h"
#include "effects/christmas_tree_effect.h"
#include "effects/stars_effect.h"
#include "effects/debug_effect.h"
#include "led_event_loop.h"

static const char* TAG = "led_base";

CRGB leds[NUM_LEDS];

LedEventLoop* ledEventLoop = NULL;

TestEffect* testEffect = NULL;
ChristmasTreeEffect* christmasTreeEffect = NULL;
StarsEffect* starsEffect = NULL;
DebugEffect* debugEffect = NULL;

// -------------------------------------------------------------------------------
void ledBaseInit () {
  ESP_LOGI (TAG, "Start init FastLED");

  FastLED.addLeds <LED_TYPE, LED_DATA_PIN> (leds, NUM_LEDS);
  FastLED.clearData ();

  ledEventLoop = new LedEventLoop;

  testEffect = new TestEffect;
  christmasTreeEffect = new ChristmasTreeEffect;
  starsEffect = new StarsEffect;
  debugEffect = new DebugEffect;

  ESP_LOGI (TAG, "End init FastLED");
}