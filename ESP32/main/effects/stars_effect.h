#ifndef M_STARS_H
#define M_STARS_H

#include <cstdint>
#include <vector>
#include "led_effect.h"
#include "FastLED.h"

// Target frames per second
#define STARS_STEPS (sizeof(StarsEffect :: palette) / sizeof(StarsEffect :: palette[0]))
#define STARS_COUNT 10

class StarsEffect: public LedEffect {
  private:
    static const CRGB palette[];

    std :: vector <int> pos;
    std :: vector <int> step;

  public:
    StarsEffect();
    virtual ~StarsEffect();

    virtual void OnStart();
    virtual void OnTimer();
    virtual const char* getName();

    static const char* name;
};
#endif
