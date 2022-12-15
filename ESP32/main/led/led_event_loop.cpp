#include "led_event_loop.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define LED_EVENT_LOOP_CORE 1
#define LED_TASK_PRIORITY 2
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

// -----------------------------------------------------
void LedEventLoop :: refreshTimerHandle (void* timer_args) 
{
  LedEventLoop* ledEffectLoop = static_cast <LedEventLoop*> (timer_args);
  ESP_ERROR_CHECK (esp_event_post_to (ledEffectLoop -> loopHandle, LED_EVENTS, TIMER_LED_EVENT, NULL, 0, portMAX_DELAY));
}

// -----------------------------------------------------
void LedEventLoop :: startEventAction (void* event_data) 
{
  if (event_data) {
    startTimer (0);

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

  esp_timer_create_args_t timerCreateArgs = {
      .callback = refreshTimerHandle,
      .arg = this,
      .dispatch_method = ESP_TIMER_TASK,
      .name = "led_refresh_timer",
      .skip_unhandled_events = true
  };
  ESP_ERROR_CHECK (esp_timer_create (&timerCreateArgs, &ledRefreshTimer));
}

// -----------------------------------------------------
void LedEventLoop :: startTimer (uint64_t period) 
{
  if (esp_timer_is_active (ledRefreshTimer)) {
    ESP_LOGI (TAG, "stop timer");
    ESP_ERROR_CHECK (esp_timer_stop (ledRefreshTimer));
  }

  if (period != 0) {
    ESP_LOGI (TAG, "start timer, period = %llu", period);
    ESP_ERROR_CHECK (esp_timer_start_periodic (ledRefreshTimer, period));
  }
}

// -----------------------------------------------------
void LedEventLoop :: postStartEvent (LedEffect* effect) 
{
  ESP_ERROR_CHECK (esp_event_post_to (loopHandle, LED_EVENTS, START_LED_EVENT, static_cast <void*> (&effect), sizeof (&effect), portMAX_DELAY));
}

// -----------------------------------------------------
void LedEventLoop :: postInteractEvent (void* data, size_t size) 
{
  ESP_ERROR_CHECK (esp_event_post_to (loopHandle, LED_EVENTS, INTERACT_LED_EVENT, data, size, portMAX_DELAY));
}

// -----------------------------------------------------
LedEventLoop :: ~LedEventLoop () 
{
  ESP_ERROR_CHECK (esp_timer_delete (ledRefreshTimer));
  ESP_ERROR_CHECK (esp_event_loop_delete (loopHandle));
}
