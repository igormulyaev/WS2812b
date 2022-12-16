#include "timer_interface.h"

// ##############################################################
// ### Constructor
// ##############################################################
Timer :: Timer (ITimer* inOwner, const char* inName)
: owner (inOwner)
{
  esp_timer_create_args_t timerCreateArgs = {
    .callback = timerHandle,
    .arg = owner,
    .dispatch_method = ESP_TIMER_TASK,
    .name = inName,
    .skip_unhandled_events = true
  };
  ESP_ERROR_CHECK (esp_timer_create (&timerCreateArgs, &timer));
}

// ##############################################################
// ### Destructor
// ##############################################################
Timer :: ~Timer ()
{
  stop ();

  ESP_ERROR_CHECK (esp_timer_delete (timer));
}

// ##############################################################
// ### Timer activation handler
// ##############################################################
void Timer :: timerHandle (void* timer_data)
{
  ITimer* iTimer = static_cast <ITimer*> (timer_data);
  iTimer -> timerAlarm ();
}

// ##############################################################
// ### Stop timer
// ##############################################################
void Timer :: stop ()
{
  if (esp_timer_is_active (timer)) {
    ESP_ERROR_CHECK (esp_timer_stop (timer));
  }
}

// ##############################################################
// ### Start timer periodic
// ##############################################################
void Timer :: startPeriodic (uint64_t period)
{
  stop ();

  if (period != 0) {
    ESP_ERROR_CHECK (esp_timer_start_periodic (timer, period));
  }
}

// ##############################################################
// ### Start timer once
// ##############################################################
void Timer :: startOnce (uint64_t timeout)
{
  stop ();

  if (timeout != 0) {
    ESP_ERROR_CHECK (esp_timer_start_once (timer, timeout));
  }
}
