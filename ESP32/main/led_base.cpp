#include "led_base.h"
#include "effects/test_effect.h"
#include "led_event_loop.h"

static const char* TAG = "led_base";

CRGB leds[NUM_LEDS];

LedEventLoop* ledEventLoop = 0;

TestEffect* testEffect = 0;

// -------------------------------------------------------------------------------
void ledBaseInit () {
  ESP_LOGI (TAG, "Start init FastLED");

  FastLED.addLeds <LED_TYPE, LED_DATA_PIN> (leds, NUM_LEDS);
  FastLED.clearData ();

  ledEventLoop = new LedEventLoop;

  testEffect = new TestEffect;

  ESP_LOGI (TAG, "End init FastLED");
}