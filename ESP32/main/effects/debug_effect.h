#ifndef M_DEBUG_EFFECT_H
#define M_DEBUG_EFFECT_H

#include "led_effect.h"
#include "FastLED.h"

class DebugEffect: public LedEffect 
{
  public:
    DebugEffect(): firstLineShift(0)
    {}
    virtual ~DebugEffect();

    virtual void OnStart (ITimer* inTimer);
    virtual void OnInteract (const void* data);
    virtual void OnTimer();
    virtual const char* getName() const;

    static const char* const name;

  private:
    int firstLineShift;

    static const char* const TAG;
    static void drawLine(int y, CRGB color);
};
#endif
