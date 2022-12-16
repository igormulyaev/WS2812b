#include "test_effect.h"
#include "led_params.h"
#include "timer_interface.h"
#include "led/led_base.h"
#include "led/rmt_led.h"
#include "esp_log.h"

// -----------------------------------------------------
const char* const TestEffect :: TAG = "test_effect";

// -----------------------------------------------------
const char* const TestEffect :: name = "Test";

// -----------------------------------------------------
const char* TestEffect :: getName() const
{
  return name;
}

// -----------------------------------------------------
void TestEffect :: OnStart (ITimer* inTimer) 
{
  ESP_LOGI (TAG, "Start");
  timer = inTimer;
  ledsClean ();
  rmtLed -> refresh ();
}

// -----------------------------------------------------
void TestEffect :: OnInteract (const void* data) 
{
  if (data) {
    switch (*static_cast <const char*> (data)) {
      case 'R':
        ESP_LOGI (TAG, "color = RED");
        timer -> startPeriodicTimer (0);
        ledsSet (0x000400);
        rmtLed -> refresh ();
        break;

      case 'G':
        ESP_LOGI (TAG, "color = GREEN");
        timer -> startPeriodicTimer (0);
        ledsSet (0x040000);
        rmtLed -> refresh ();
        break;

      case 'B':
        ESP_LOGI (TAG, "color = BLUE");
        timer -> startPeriodicTimer (0);
        ledsSet (0x000004);
        rmtLed -> refresh ();
        break;

      case 'L':
        ESP_LOGI (TAG, "Start running light");
        pos = LED_COUNT - 1;
        timer -> startPeriodicTimer (1000000 / 30);
        break;
        
      default:
        ESP_LOGI(TAG, "color = BLACK");
        timer -> startPeriodicTimer (0);
        ledsSet (RGB::Black);
        rmtLed -> refresh ();
    }
  }
  else {
    ESP_LOGE(TAG, "interactData NULL");
  }
}

// -----------------------------------------------------
void TestEffect :: OnTimer () 
{
  leds[pos] = RGB::Black;
  pos = (pos + 1) % LED_COUNT;
  leds[pos] = 0x040404;
  rmtLed -> refresh ();
}

// -----------------------------------------------------
TestEffect :: ~TestEffect () 
{
}
