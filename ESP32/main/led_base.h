#ifndef M_LED_BASE_H
#define M_LED_BASE_H

#include "FastLED.h"
#include "led_params.h"

extern CRGB leds[NUM_LEDS];

class LedEventLoop;
class TestEffect;
class ChristmasTree;
class StarsEffect;

extern LedEventLoop* ledEventLoop;
extern TestEffect* testEffect;
extern ChristmasTree* christmasTree;
extern StarsEffect* starsEffect;

void ledBaseInit ();

#endif