#ifndef M_LED_BASE_H
#define M_LED_BASE_H

#include "led_params.h"
#include "pixel.h"

extern RGB leds[LED_COUNT];

void ledsClean ();
void ledsSet (RGB color);
void ledBaseInit ();

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

class RmtLed;
extern RmtLed* rmtLed;

#endif