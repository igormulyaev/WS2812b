#ifndef M_LED_BASE_H
#define M_LED_BASE_H

#include "FastLED.h"
#include "led_params.h"

extern CRGB leds[NUM_LEDS];

class LedEventLoop;
class TestEffect;
class ChristmasTreeEffect;
class StarsEffect;
class DebugEffect;

extern LedEventLoop* ledEventLoop;
extern TestEffect* testEffect;
extern ChristmasTreeEffect* christmasTreeEffect;
extern StarsEffect* starsEffect;
extern DebugEffect* debugEffect;

void ledBaseInit ();

#endif