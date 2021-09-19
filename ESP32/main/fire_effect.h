#ifndef M_FIRE_EFFECT_H
#define M_FIRE_EFFECT_H

#include <cstdint>
#include "led_effect.h"
#include "led_params.h"

class CFireEffect: public CLedEffect {
  private:
    // Field to compute effect
    // Left -> Right, Top -> Bottom
    uint8_t field[NUM_LEDS]; 

    void updateBottomLine();
    void updateField();
    void updateLeds();


  public:
    virtual void OnStart();
    virtual void OnTimer();
    virtual ~CFireEffect();
};
#endif
