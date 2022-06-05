#include "debug_effect.h"
#include "led_params.h"
#include "timer_interface.h"
#include "led_base.h"

// Refresh frequency, Hz
#define M_REFRESH_FREQ 5

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

  firstLineShift = 0;

  inTimer -> startTimer (1000000 / M_REFRESH_FREQ);
}

// -----------------------------------------------------
void DebugEffect :: drawLine(int y, CRGB color)
{
  int pos = y;
  for (int i = 1; i < LED_WIDTH / 2; ++i) {
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
  drawLine (pos,  0x000600); // Blue
  pos = (pos + 4) % LED_HEIGHT;
  drawLine (pos,  0x000006); // Red
  pos = (pos + 4) % LED_HEIGHT;
  drawLine (pos, 0x000303); // Magenta
  pos = (pos + 4) % LED_HEIGHT;
  drawLine (pos, 0x060000); // Green
  pos = (pos + 4) % LED_HEIGHT;
  drawLine (pos, 0x030003); // Cyan
  pos = (pos + 4) % LED_HEIGHT;
  drawLine (pos, 0x030300); // Yellow
  pos = (pos + 4) % LED_HEIGHT;
  drawLine (pos, 0x020202); // White

  FastLED.show();
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
