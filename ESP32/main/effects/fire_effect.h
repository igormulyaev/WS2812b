#ifndef M_FIRE_EFFECT_H
#define M_FIRE_EFFECT_H

#include <cstdint>
#include "led_effect.h"
#include "led/led_base.h"

class FireEffect: public LedEffect {
  private:
    static const RGB firePalette[256];
    // Field to compute effect
    // Left -> Right, Top -> Bottom
    uint8_t field [LED_COUNT]; 

    void updateBottomLine();
    void updateField();
    void updateLeds();

    bool skipTick;
    int cntBottom;

  public:
    virtual void OnStart();
    virtual void OnTimer();
    virtual ~FireEffect();
};
#endif
