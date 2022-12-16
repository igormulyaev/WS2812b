#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "esp_timer.h"

class Director
{
  public:
    Director ();
    ~Director ();

  private:
    esp_timer_handle_t timer;
    static void timerHandle (void* timer_data);
    
    Director (const Director &) = delete;
    Director & operator=(const Director &) = delete;
};

#endif