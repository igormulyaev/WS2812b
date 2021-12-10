#ifndef M_LED_BASE_H
#define M_LED_BASE_H

#include "FastLED.h"
#include "led_params.h"

extern CRGB leds[NUM_LEDS];

void ledBaseInit ();

#endif