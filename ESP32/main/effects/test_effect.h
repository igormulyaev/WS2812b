#ifndef M_TEST_EFFECT_H
#define M_TEST_EFFECT_H

#include "led_effect.h"
#include "FastLED.h"

// Target frames per second

class TestEffect: public LedEffect {
  private:
    static const char* TAG;
  public:
    TestEffect() {}

    virtual void OnStart(ITimer* timer);
    virtual void OnInteract(const void* data);
    virtual void OnTimer();
    virtual ~TestEffect();
};
#endif
