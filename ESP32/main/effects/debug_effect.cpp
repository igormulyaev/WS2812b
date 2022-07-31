#include "debug_effect.h"
#include "led_params.h"
#include "timer_interface.h"
#include "led_base.h"

// Refresh frequency, Hz
#define M_REFRESH_FREQ 2

// -----------------------------------------------------
const char* const DebugEffect :: TAG = "debug_effect";

// -----------------------------------------------------
const char* const DebugEffect :: name = "Debug";

// -----------------------------------------------------
const char* DebugEffect :: getName() const
{
  return name;
}

// -----------------------------------------------------
void DebugEffect :: OnStart(ITimer* inTimer) 
{
  ESP_LOGI(TAG, "Start");
  FastLED.clearData();
  FastLED.show();

  firstLineShift = 0;

  inTimer -> startTimer (1000000 / M_REFRESH_FREQ);
}

// -----------------------------------------------------
void DebugEffect :: drawLine(int y, CRGB color)
{
  int pos = y;
  for (int i = 1; i <= LED_WIDTH / 2; ++i) {
    leds[pos] = color;
    leds[pos + (LED_HEIGHT * 2 - 1) - y * 2] = color;
    pos += LED_HEIGHT * 2;
  }
}

// -----------------------------------------------------
void DebugEffect :: OnTimer() 
{
  FastLED.clearData();

  int pos = firstLineShift;
  // GBR
  drawLine (pos,  0x000c00); // Blue
  pos = (pos + 4) % LED_HEIGHT;
  drawLine (pos,  0x00000c); // Red
  pos = (pos + 4) % LED_HEIGHT;
  drawLine (pos, 0x000606); // Magenta
  pos = (pos + 4) % LED_HEIGHT;
  drawLine (pos, 0x0c0000); // Green
  pos = (pos + 4) % LED_HEIGHT;
  drawLine (pos, 0x060006); // Cyan
  pos = (pos + 4) % LED_HEIGHT;
  drawLine (pos, 0x060600); // Yellow
  pos = (pos + 4) % LED_HEIGHT;
  drawLine (pos, 0x040404); // White

  int64_t mcsStart = esp_timer_get_time();
  FastLED.show();
  int64_t mcsTaken = esp_timer_get_time() - mcsStart;
  ESP_LOGI (TAG, "%lld mcs", mcsTaken);
}

// -----------------------------------------------------
void DebugEffect :: OnInteract(const void*) 
{
  firstLineShift = (firstLineShift + 1) % LED_HEIGHT;
}

// -----------------------------------------------------
DebugEffect :: ~DebugEffect() 
{
}
