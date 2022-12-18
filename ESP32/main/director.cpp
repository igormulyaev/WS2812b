#include "director.h"

// ############################################################
Director :: Director ()
: timer (this, "director_timer")
{}

// ############################################################
Director :: ~Director ()
{}

// ############################################################
void Director :: startPeriodicTimer (uint64_t period) 
{
  timer.startPeriodic (period);
}

// ############################################################
void Director :: startOnceTimer (uint64_t timeout) 
{
  timer.startOnce (timeout);
}


// ############################################################
// ### Executes when the timer alarms
// ############################################################
void Director :: timerAlarm () 
{
}


// ############################################################
Director* director = NULL;
