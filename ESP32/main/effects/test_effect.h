#ifndef M_TEST_EFFECT_H
#define M_TEST_EFFECT_H

#include "led_effect.h"
#include <cstddef>


// Target frames per second

class TestEffect: public LedEffect 
{
  public:
    TestEffect():
      pos(0),
      timer (0)
    {}
    virtual ~TestEffect();

    virtual void OnStart (ITimer* inTimer);
    virtual void OnInteract (const void* data);
    virtual void OnTimer();
    virtual const char* getName() const;

    static const char* const name;

  private:
    static const char* const TAG;
    size_t pos;
    ITimer* timer;
};
#endif
