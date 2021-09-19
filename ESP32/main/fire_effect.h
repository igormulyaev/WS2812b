#ifndef M_FIRE_EFFECT_H
#define M_FIRE_EFFECT_H

#include <cstdint>
#include "led_effect.h"
#include "FastLED.h"

class CFireEffect: public CLedEffect {
  private:

  public:
    virtual void OnStart();
    virtual void OnTimer();
    virtual ~CFireEffect();
};
#endif
