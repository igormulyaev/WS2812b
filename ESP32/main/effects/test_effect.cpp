#include "test_effect.h"
#include "led_params.h"

// -----------------------------------------------------
const char* TestEffect :: TAG = "test_effect";

// -----------------------------------------------------
const char* const TestEffect :: name = "Test";

// -----------------------------------------------------
const char* TestEffect :: getName() const
{
  return name;
}

// -----------------------------------------------------
void TestEffect :: OnStart(ITimer* timer) {
  ESP_LOGI(TAG, "Start");
  FastLED.clearData();
  FastLED.show();
}

// -----------------------------------------------------
void TestEffect :: OnInteract(const void* data) {
  if (data) {
    CRGB color;
    switch (*static_cast<const char*>(data)) {
      case 'R':
        ESP_LOGI(TAG, "color = RED");
        color = 0x000400;
        break;
      case 'G':
        ESP_LOGI(TAG, "color = GREEN");
        color = 0x040000;
        break;
      case 'B':
        ESP_LOGI(TAG, "color = BLUE");
        color = 0x000004;
        break;
      default:
        ESP_LOGI(TAG, "color = BLACK");
        color = CRGB::Black;
    }
    FastLED.showColor(color);
  }
  else {
    ESP_LOGE(TAG, "interactData NULL");
  }
}

// -----------------------------------------------------
void TestEffect :: OnTimer() {
}

// -----------------------------------------------------
TestEffect :: ~TestEffect() {
}
