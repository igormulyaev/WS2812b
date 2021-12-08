#include "led_event_loop.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define M_LED_EVENT_LOOP_CORE 1

static const char* TAG = "led_event_loop";

// definition of the LED task events family
ESP_EVENT_DEFINE_BASE(LED_EVENTS);         

// -----------------------------------------------------
void CLedEffectLoop :: startEventHandler(void* handler_args, esp_event_base_t base, int32_t id, void* event_data) {
  CLedEffectLoop* ledEffectLoop = static_cast<CLedEffectLoop*>(handler_args);
  ledEffectLoop -> startEventAction(event_data);
}

// -----------------------------------------------------
void CLedEffectLoop :: timerEventHandler(void* handler_args, esp_event_base_t base, int32_t id, void* event_data) {
  CLedEffectLoop* ledEffectLoop = static_cast<CLedEffectLoop*>(handler_args);
  ledEffectLoop -> timerEventAction();
}

// -----------------------------------------------------
void CLedEffectLoop :: interactEventHandler(void* handler_args, esp_event_base_t base, int32_t id, void* event_data) {
  CLedEffectLoop* ledEffectLoop = static_cast<CLedEffectLoop*>(handler_args);
  ledEffectLoop -> interactEventAction(event_data);
}

// -----------------------------------------------------
void CLedEffectLoop :: refreshTimerHandle(void* timer_args) {
  CLedEffectLoop* ledEffectLoop = static_cast<CLedEffectLoop*>(timer_args);
  ESP_ERROR_CHECK(esp_event_post_to(ledEffectLoop -> loopHandle, LED_EVENTS, TIMER_LED_EVENT, NULL, 0, portMAX_DELAY));
}

// -----------------------------------------------------
void CLedEffectLoop :: startEventAction(void* event_data) {
  if (event_data) {
    StartTimer(0);

    ledEffect = *static_cast<CLedEffect**>(event_data);
    if (ledEffect) {
      ESP_LOGI(TAG, "call OnStart");
      ledEffect -> OnStart(this);
    }
    else {
      ESP_LOGI(TAG, "ledEffect NULL");
    }
  }
  else {
    ESP_LOGE(TAG, "startEventAction NULL");
  }
}

// -----------------------------------------------------
void CLedEffectLoop :: timerEventAction() {
  if (ledEffect) {
    ledEffect -> OnTimer();
  }
}

// -----------------------------------------------------
void CLedEffectLoop :: interactEventAction(void* event_data) {
  ESP_LOGI(TAG, "interact event action");
  if (ledEffect) {
    ledEffect -> OnInteract(event_data);
  }
}

// -----------------------------------------------------
CLedEffectLoop :: CLedEffectLoop() {
  ledEffect = NULL;

  ESP_LOGI(TAG, "starting led event loop");

  esp_event_loop_args_t loopArgs = {
      .queue_size = 5,
      .task_name = "led_event_loop_task", // task will be created
      .task_priority = uxTaskPriorityGet(NULL),
      .task_stack_size = 2048,
      .task_core_id = M_LED_EVENT_LOOP_CORE
  };
  // Create the event loop
  ESP_ERROR_CHECK(esp_event_loop_create(&loopArgs, &loopHandle));

  ESP_ERROR_CHECK(esp_event_handler_instance_register_with(loopHandle, LED_EVENTS, START_LED_EVENT, CLedEffectLoop :: startEventHandler, this, NULL));
  ESP_ERROR_CHECK(esp_event_handler_instance_register_with(loopHandle, LED_EVENTS, TIMER_LED_EVENT, CLedEffectLoop :: timerEventHandler, this, NULL));
  ESP_ERROR_CHECK(esp_event_handler_instance_register_with(loopHandle, LED_EVENTS, INTERACT_LED_EVENT, CLedEffectLoop :: interactEventHandler, this, NULL));

  esp_timer_create_args_t timerCreateArgs = {
      .callback = refreshTimerHandle,
      .arg = this,
      .dispatch_method = ESP_TIMER_TASK,
      .name = "led_refresh_timer",
      .skip_unhandled_events = true
  };
  ESP_ERROR_CHECK(esp_timer_create(&timerCreateArgs, &ledRefreshTimer));
}

// -----------------------------------------------------
void CLedEffectLoop :: StartTimer(uint64_t period) {
  if (esp_timer_is_active(ledRefreshTimer)) {
    ESP_LOGI(TAG, "stop timer");
    ESP_ERROR_CHECK(esp_timer_stop(ledRefreshTimer));
  }

  if (period != 0) {
    ESP_LOGI(TAG, "start timer, period = %llu", period);
    ESP_ERROR_CHECK(esp_timer_start_periodic(ledRefreshTimer, period));
  }
}

// -----------------------------------------------------
void CLedEffectLoop :: postStartEvent(CLedEffect* effect) {
  ESP_ERROR_CHECK(esp_event_post_to(loopHandle, LED_EVENTS, START_LED_EVENT, static_cast<void*>(&effect), sizeof(&effect), portMAX_DELAY));
}

// -----------------------------------------------------
void CLedEffectLoop :: postInteractEvent(void* data, size_t size) {
  ESP_ERROR_CHECK(esp_event_post_to(loopHandle, LED_EVENTS, INTERACT_LED_EVENT, data, size, portMAX_DELAY));
}

// -----------------------------------------------------
CLedEffectLoop :: ~CLedEffectLoop() {
  ESP_ERROR_CHECK(esp_timer_delete(ledRefreshTimer));
  ESP_ERROR_CHECK(esp_event_loop_delete(loopHandle));
}
