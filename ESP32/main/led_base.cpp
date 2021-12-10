#include "led_base.h"

static const char* TAG = "led_base";

CRGB leds[NUM_LEDS];

// -------------------------------------------------------------------------------
void ledBaseInit () {
  ESP_LOGI (TAG, "Start init FastLED");

  FastLED.addLeds <LED_TYPE, LED_DATA_PIN> (leds, NUM_LEDS);
  FastLED.clearData ();

  ESP_LOGI (TAG, "End init FastLED");
}