#ifndef M_TIMER_INTERFACE_H
#define M_TIMER_INTERFACE_H

/*
  Timer interface
*/

class ITimer {
  public:
    virtual void StartTimer (uint64_t period) = 0;
    virtual ~ITimer () {};
};

#endif
