#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

//#include <cstdint>
#include "esp_timer.h"

class Timer;

// ##############################################################
// ### Timer interface, base class for timer owner
// ##############################################################
class ITimer 
{
  public:
    virtual void startPeriodicTimer (uint64_t period) = 0;
    virtual void startOnceTimer (uint64_t timeout) = 0;
    virtual ~ITimer () {};

  private:
    virtual void timerAlarm () = 0;

  friend class Timer;
};

// ##############################################################
// ### Timer as is
// ##############################################################
class Timer
{
  public:
    Timer (ITimer* inOwner, const char* inName);
    ~Timer ();

    void stop();
    void startPeriodic (uint64_t period);
    void startOnce (uint64_t timeout);

  private:
    ITimer* owner;
    esp_timer_handle_t timer;

    static void timerHandle (void* timer_data);
    
    Timer (const Timer &) = delete;
    Timer & operator=(const Timer &) = delete;
};

#endif
