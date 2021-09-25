#include "fire_effect.h"
#include "led_params.h"

#define FIRE_K_LEFT 20
#define FIRE_K_CENTER 92
#define FIRE_K_RIGHT 20
#define FIRE_K_BOTTOM 92
#define FIRE_BOTTOM_TICKS 6

// -----------------------------------------------------
void CFireEffect :: OnTimer() {
  if (!skipTick) {
    FastLED.show();

    if (cntBottom == 0) {
      updateBottomLine();
      cntBottom = FIRE_BOTTOM_TICKS;
    }
    --cntBottom;

    updateField();
    updateLeds();
  }
  skipTick = !skipTick;
};

// -----------------------------------------------------
void CFireEffect :: OnStart() {
  for (int pos = 0; pos < NUM_LEDS; ++pos) {
    leds[pos] = CRGB::Black;
  }
  skipTick = false;
  cntBottom = 0;
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
  // Pointer to current target line 
  uint8_t *tgt = field;

  for (int cnt_lines = LED_HEIGHT - 1; cnt_lines; --cnt_lines, tgt += LED_WIDTH) {
    // Pointers to source lines
    uint8_t const *src0 = tgt + LED_WIDTH;
    uint8_t const *src1 = src0 + (cnt_lines > 1? LED_WIDTH: 0);

    for (int x = 0; x < LED_WIDTH; ++x) {
      int v = src0[(x + LED_WIDTH - 1) % LED_WIDTH] * FIRE_K_LEFT +
              src0[x] * FIRE_K_CENTER +
              src0[(x + 1) % LED_WIDTH] * FIRE_K_RIGHT +
              src1[x] * FIRE_K_BOTTOM;
      tgt[x] = v >> 8;
    }
  }
}

// -----------------------------------------------------
void CFireEffect :: updateLeds() {
  CRGB *tgt = leds;
  uint8_t const *src = field;
  // difference between field positions to get next led value
  int diff = LED_WIDTH;

  for (int cols = LED_WIDTH; cols; --cols) {
    for (int lines = LED_HEIGHT; lines; --lines) {
      *tgt++ = firePalette[*src];
      src += diff;
    }
    diff = -diff; // reverse direction for next column
    src += diff + 1; // move to beginning of next column
  }
}

// -----------------------------------------------------
const CRGB CFireEffect :: firePalette[256] = {
  0x000000,
  0x000000,
  0x000000,
  0x000000,
  0x000000,
  0x000000,
  0x000000,
  0x000000,
  0x000000,
  0x000000,
  0x000000,
  0x000100,
  0x000100,
  0x000100,
  0x000100,
  0x000100,
  0x000100,
  0x000200,
  0x000200,
  0x000200,
  0x000200,
  0x000200,
  0x000300,
  0x000300,
  0x000300,
  0x000400,
  0x000400,
  0x000400,
  0x000500,
  0x000500,
  0x000500,
  0x000600,
  0x000600,
  0x000700,
  0x000700,
  0x000800,
  0x000800,
  0x000900,
  0x000900,
  0x000A00,
  0x000A00,
  0x000B00,
  0x000B00,
  0x000C00,
  0x000D00,
  0x000D00,
  0x000E00,
  0x000F00,
  0x000F00,
  0x001000,
  0x001100,
  0x001200,
  0x001200,
  0x001300,
  0x001400,
  0x001500,
  0x001600,
  0x001700,
  0x001700,
  0x001900,
  0x001900,
  0x001A00,
  0x001B00,
  0x001C00,
  0x001D00,
  0x001E00,
  0x001F00,
  0x002100,
  0x002100,
  0x002300,
  0x002300,
  0x002500,
  0x002600,
  0x002700,
  0x002800,
  0x002A00,
  0x002B00,
  0x002C00,
  0x002D00,
  0x002F00,
  0x003000,
  0x003100,
  0x003200,
  0x003400,
  0x003500,
  0x003700,
  0x003700,
  0x003700,
  0x003700,
  0x003700,
  0x003700,
  0x003700,
  0x003700,
  0x003700,
  0x003700,
  0x003700,
  0x013700,
  0x013700,
  0x013700,
  0x013700,
  0x013700,
  0x013700,
  0x023700,
  0x023700,
  0x023700,
  0x023700,
  0x023700,
  0x033700,
  0x033700,
  0x033700,
  0x043700,
  0x043700,
  0x043700,
  0x053700,
  0x053700,
  0x053700,
  0x063700,
  0x063700,
  0x073700,
  0x073700,
  0x083700,
  0x083700,
  0x093700,
  0x093700,
  0x0A3700,
  0x0A3700,
  0x0B3700,
  0x0B3700,
  0x0C3700,
  0x0D3700,
  0x0D3700,
  0x0E3700,
  0x0F3700,
  0x0F3700,
  0x103700,
  0x113700,
  0x123700,
  0x123700,
  0x133700,
  0x143700,
  0x153700,
  0x163700,
  0x173700,
  0x173700,
  0x193700,
  0x193700,
  0x1A3700,
  0x1B3700,
  0x1C3700,
  0x1D3700,
  0x1E3700,
  0x1F3700,
  0x213700,
  0x213700,
  0x233700,
  0x233700,
  0x253700,
  0x263700,
  0x273700,
  0x283700,
  0x2A3700,
  0x2B3700,
  0x2C3700,
  0x2D3700,
  0x2F3700,
  0x303700,
  0x313700,
  0x323700,
  0x343700,
  0x353700,
  0x373700,
  0x373700,
  0x373700,
  0x373700,
  0x373700,
  0x373700,
  0x373700,
  0x373700,
  0x373700,
  0x373700,
  0x373700,
  0x373701,
  0x373701,
  0x373701,
  0x373701,
  0x373701,
  0x373701,
  0x373702,
  0x373702,
  0x373702,
  0x373702,
  0x373702,
  0x373703,
  0x373703,
  0x373703,
  0x373704,
  0x373704,
  0x373704,
  0x373705,
  0x373705,
  0x373705,
  0x373706,
  0x373706,
  0x373707,
  0x373707,
  0x373708,
  0x373708,
  0x373709,
  0x373709,
  0x37370A,
  0x37370A,
  0x37370B,
  0x37370B,
  0x37370C,
  0x37370D,
  0x37370D,
  0x37370E,
  0x37370F,
  0x37370F,
  0x373710,
  0x373711,
  0x373712,
  0x373712,
  0x373713,
  0x373714,
  0x373715,
  0x373716,
  0x373717,
  0x373717,
  0x373719,
  0x373719,
  0x37371A,
  0x37371B,
  0x37371C,
  0x37371D,
  0x37371E,
  0x37371F,
  0x373721,
  0x373721,
  0x373723,
  0x373723,
  0x373725,
  0x373726,
  0x373727,
  0x373728,
  0x37372A,
  0x37372B,
  0x37372C,
  0x37372D,
  0x37372F,
  0x373730,
  0x373731,
  0x373732,
  0x373734,
  0x373735,
  0x373737
};
