#include "led_event_loop.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define LED_EVENT_LOOP_CORE 1
#define LED_TASK_PRIORITY 1
#define LED_TASK_STACK_SIZE 4096

static const char* TAG = "led_event_loop";

// definition of the LED task events family
ESP_EVENT_DEFINE_BASE (LED_EVENTS);         

// -----------------------------------------------------
void LedEventLoop :: startEventHandler (void* handler_args, esp_event_base_t base, int32_t id, void* event_data) 
{
  LedEventLoop* ledEffectLoop = static_cast <LedEventLoop*> (handler_args);
  ledEffectLoop -> startEventAction (event_data);
}

// -----------------------------------------------------
void LedEventLoop :: timerEventHandler (void* handler_args, esp_event_base_t base, int32_t id, void* event_data) 
{
  LedEventLoop* ledEffectLoop = static_cast <LedEventLoop*> (handler_args);
  ledEffectLoop -> timerEventAction ();
}

// -----------------------------------------------------
void LedEventLoop :: interactEventHandler (void* handler_args, esp_event_base_t base, int32_t id, void* event_data) 
{
  LedEventLoop* ledEffectLoop = static_cast <LedEventLoop*> (handler_args);
  ledEffectLoop -> interactEventAction (event_data);
}

// ############################################################
// ### Executes when the timer alarms
// ############################################################
void LedEventLoop :: timerAlarm () 
{
  postTimerEvent ();
}

// ############################################################
void LedEventLoop :: startPeriodicTimer (uint64_t period) 
{
  ledRefreshTimer.startPeriodic (period);
}

// ############################################################
void LedEventLoop :: startOnceTimer (uint64_t timeout) 
{
  ledRefreshTimer.startOnce (timeout);
}

// -----------------------------------------------------
void LedEventLoop :: startEventAction (void* event_data) 
{
  if (event_data) {
    ledRefreshTimer.stop ();

    ledEffect = *static_cast <LedEffect**> (event_data);
    if (ledEffect) {
      ESP_LOGI (TAG, "call OnStart");
      ledEffect -> OnStart (this);
    }
    else {
      ESP_LOGI (TAG, "ledEffect NULL");
    }
  }
  else {
    ESP_LOGE (TAG, "startEventAction NULL");
  }
}

// -----------------------------------------------------
void LedEventLoop :: timerEventAction () 
{
  if (ledEffect) {
    ledEffect -> OnTimer ();
  }
}

// -----------------------------------------------------
void LedEventLoop :: interactEventAction (void* event_data) 
{
  ESP_LOGI (TAG, "interact event action");
  if (ledEffect) {
    ledEffect -> OnInteract (event_data);
  }
}

// -----------------------------------------------------
LedEventLoop :: LedEventLoop () 
: ledRefreshTimer (this, "led_refresh_timer")
{
  ledEffect = NULL;

  ESP_LOGI (TAG, "starting led event loop");

  esp_event_loop_args_t loopArgs = {
      .queue_size = 5,
      .task_name = "led_event_loop_task", // task will be created
      .task_priority = LED_TASK_PRIORITY,
      .task_stack_size = LED_TASK_STACK_SIZE,
      .task_core_id = LED_EVENT_LOOP_CORE
  };
  // Create the event loop
  ESP_ERROR_CHECK (esp_event_loop_create (&loopArgs, &loopHandle));

  ESP_ERROR_CHECK (esp_event_handler_instance_register_with (loopHandle, LED_EVENTS, START_LED_EVENT, startEventHandler, this, NULL));
  ESP_ERROR_CHECK (esp_event_handler_instance_register_with (loopHandle, LED_EVENTS, TIMER_LED_EVENT, timerEventHandler, this, NULL));
  ESP_ERROR_CHECK (esp_event_handler_instance_register_with (loopHandle, LED_EVENTS, INTERACT_LED_EVENT, interactEventHandler, this, NULL));
}

// ############################################################
// ### Post start event
// ############################################################
void LedEventLoop :: postStartEvent (LedEffect* effect) 
{
  ESP_ERROR_CHECK (esp_event_post_to (loopHandle, LED_EVENTS, START_LED_EVENT, static_cast <void*> (&effect), sizeof (&effect), portMAX_DELAY));
}

// ############################################################
// ### Post interact event
// ############################################################
void LedEventLoop :: postInteractEvent (void* data, size_t size) 
{
  ESP_ERROR_CHECK (esp_event_post_to (loopHandle, LED_EVENTS, INTERACT_LED_EVENT, data, size, portMAX_DELAY));
}

// ############################################################
// ### Post timer event
// ### Called from timer alarm, and can be called manually
// ############################################################
void LedEventLoop :: postTimerEvent () 
{
  ESP_ERROR_CHECK (esp_event_post_to (loopHandle, LED_EVENTS, TIMER_LED_EVENT, NULL, 0, portMAX_DELAY));
}

// ############################################################
LedEventLoop :: ~LedEventLoop () 
{
  ESP_ERROR_CHECK (esp_event_loop_delete (loopHandle));
}
