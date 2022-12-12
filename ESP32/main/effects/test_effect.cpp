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
        timer -> startTimer (0);
        ledsSet (0x000400);
        break;

      case 'G':
        ESP_LOGI (TAG, "color = GREEN");
        timer -> startTimer (0);
        ledsSet (0x040000);
        break;

      case 'B':
        ESP_LOGI (TAG, "color = BLUE");
        timer -> startTimer (0);
        ledsSet (0x000004);
        break;

      case 'L':
        ESP_LOGI (TAG, "Start running light");
        pos = LED_COUNT - 1;
        timer -> startTimer (1000000 / 5);
        break;
        
      default:
        ESP_LOGI(TAG, "color = BLACK");
        timer -> startTimer (0);
        ledsSet (RGB::Black);
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
