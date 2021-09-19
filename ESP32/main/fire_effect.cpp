#include "fire_effect.h"
#include "led_params.h"

// -----------------------------------------------------
void CFireEffect :: OnTimer() {
  FastLED.show();
};

// -----------------------------------------------------
void CFireEffect :: OnStart() {
  for (int pos = 0; pos < NUM_LEDS; ++pos) {
    leds[pos] = CRGB::Black;
  }
}

// -----------------------------------------------------
CFireEffect :: ~CFireEffect() {
}
