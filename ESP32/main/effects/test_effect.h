#ifndef M_TEST_EFFECT_H
#define M_TEST_EFFECT_H

#include "led_effect.h"
#include "FastLED.h"

// Target frames per second

class TestEffect: public LedEffect 
{
  public:
    TestEffect() {}
    virtual ~TestEffect();

    virtual void OnStart(ITimer* timer);
    virtual void OnInteract(const void* data);
    virtual void OnTimer();
    virtual const char* getName();

    static const char* const name;

  private:
    static const char* TAG;
};
#endif
