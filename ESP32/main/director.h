#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "timer_interface.h"

class Director: public ITimer
{
  public:
    Director ();
    virtual ~Director ();

    virtual void startPeriodicTimer (uint64_t period);
    virtual void startOnceTimer (uint64_t timeout);

  private:
    virtual void timerAlarm ();
    Timer timer;
    
    Director (const Director &) = delete;
    Director & operator=(const Director &) = delete;
};

extern Director* director;

#endif