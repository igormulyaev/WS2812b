#ifndef M_LED_EVENT_LOOP_H
#define M_LED_EVENT_LOOP_H

#include "esp_event.h"
#include "esp_timer.h"

#include "effects/led_effect.h"
#include "timer_interface.h"

/*
  LED event loop process
*/

// declaration of the LED task events family
ESP_EVENT_DECLARE_BASE(LED_EVENTS);         

// List of LED events
enum {
    START_LED_EVENT,
    TIMER_LED_EVENT,
    INTERACT_LED_EVENT
};

class LedEventLoop : public ITimer {
  public:
    LedEventLoop();
    ~LedEventLoop();

    void postStartEvent(LedEffect* effect);
    void postInteractEvent(void* data, size_t size);

    virtual void startTimer(uint64_t period);

    const LedEffect* getLedEffect() const { return ledEffect; }

  private:
    esp_event_loop_handle_t loopHandle;
    esp_timer_handle_t ledRefreshTimer;

    LedEffect* ledEffect;

    static void startEventHandler (void* handler_args, esp_event_base_t base, int32_t id, void* event_data);
    static void timerEventHandler (void* handler_args, esp_event_base_t base, int32_t id, void* event_data);
    static void interactEventHandler (void* handler_args, esp_event_base_t base, int32_t id, void* event_data);

    static void refreshTimerHandle (void* timer_data);

    void timerEventAction();
    void startEventAction (void* event_data);
    void interactEventAction (void* event_data);

    LedEventLoop(const LedEventLoop &) = delete;
    LedEventLoop & operator=(const LedEventLoop &) = delete;

};

// ---------------------------------------------------


#endif
