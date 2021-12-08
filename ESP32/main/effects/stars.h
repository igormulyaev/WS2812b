#ifndef M_STARS_H
#define M_STARS_H

#include <cstdint>
#include <vector>
#include "led_effect.h"
#include "FastLED.h"

// Target frames per second
#define STARS_STEPS (sizeof(CStars :: palette) / sizeof(CStars :: palette[0]))
#define STARS_COUNT 10

class CStars: public CLedEffect {
  private:
    static const CRGB palette[];

    std :: vector <int> pos;
    std :: vector <int> step;

  public:
    CStars();

    virtual void OnStart();
    virtual void OnTimer();
    virtual ~CStars();
};
#endif
