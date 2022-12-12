#ifndef M_TIMER_INTERFACE_H
#define M_TIMER_INTERFACE_H

#include <cstdint>
/*
  Timer interface
*/

class ITimer {
  public:
    virtual void startTimer (uint64_t period) = 0;
    virtual ~ITimer () {};
};

#endif
