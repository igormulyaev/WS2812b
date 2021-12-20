#ifndef M_LED_BASE_H
#define M_LED_BASE_H

#include "FastLED.h"
#include "led_params.h"

extern CRGB leds[NUM_LEDS];

class LedEventLoop;
class TestEffect;

extern LedEventLoop* ledEventLoop;
extern TestEffect* testEffect;

void ledBaseInit ();

#endif