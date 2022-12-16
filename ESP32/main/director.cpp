#include "director.h"

Director :: Director ()
{
  esp_timer_create_args_t timerCreateArgs = {
      .callback = timerHandle,
      .arg = this,
      .dispatch_method = ESP_TIMER_TASK,
      .name = "director_timer",
      .skip_unhandled_events = true
  };
  ESP_ERROR_CHECK (esp_timer_create (&timerCreateArgs, &timer));
}

