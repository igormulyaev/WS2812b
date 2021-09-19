#include "fire_effect.h"
#include "led_params.h"

// -----------------------------------------------------
void CFireEffect :: OnTimer() {
  FastLED.show();

  updateBottomLine();
  updateField();
  updateLeds();
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

// -----------------------------------------------------
void CFireEffect :: updateBottomLine() {
  // Pointer to bottom line
  uint8_t *f = &field[NUM_LEDS - LED_WIDTH];

  // Randomize all bottom pixels
  for (int cnt = LED_WIDTH; cnt; --cnt) {
    *f++ = esp_random() & 0xff;
  }
}

// -----------------------------------------------------
void CFireEffect :: updateField() {
}

// -----------------------------------------------------
void CFireEffect :: updateLeds() {
}
