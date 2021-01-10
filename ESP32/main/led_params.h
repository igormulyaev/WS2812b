#ifndef M_LED_PARAMS_H
#define M_LED_PARAMS_H

#include "FastLED.h"

#define LED_WIDTH 16
#define LED_HEIGHT 30

#define NUM_LEDS (LED_WIDTH * LED_HEIGHT)
#define LED_DATA_PIN 13 
#define LED_TYPE    WS2812B
#define LED_FPS 50

extern CRGB leds[NUM_LEDS];

#endif