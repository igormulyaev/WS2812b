#include "fire_effect.h"
#include "led_params.h"
#include "led/rmt_led.h"
#include "esp_random.h"

#define FIRE_K_LEFT 20
#define FIRE_K_CENTER 92
#define FIRE_K_RIGHT 20
#define FIRE_K_BOTTOM 92
#define FIRE_BOTTOM_TICKS 6

// -----------------------------------------------------
void FireEffect :: OnTimer () {
  if (!skipTick) {
    rmtLed -> refresh ();

    if (cntBottom == 0) {
      updateBottomLine ();
      cntBottom = FIRE_BOTTOM_TICKS;
    }
    --cntBottom;

    updateField ();
    updateLeds ();
  }
  skipTick = !skipTick;
};

// -----------------------------------------------------
void FireEffect :: OnStart () 
{
  for (int pos = 0; pos < LED_COUNT; ++pos) {
    leds[pos] = RGB::Black;
  }
  skipTick = false;
  cntBottom = 0;
}

// -----------------------------------------------------
FireEffect :: ~FireEffect () 
{
}

// -----------------------------------------------------
void FireEffect :: updateBottomLine () 
{
  // Pointer to bottom line
  uint8_t *f = &field[LED_COUNT - LED_WIDTH];

  // Randomize all bottom pixels
  for (int cnt = LED_WIDTH; cnt; --cnt) {
    *f++ = esp_random() & 0xff;
  }
}

// -----------------------------------------------------
void FireEffect :: updateField () 
{
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
void FireEffect :: updateLeds() {
  RGB *tgt = leds;
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
const RGB FireEffect :: firePalette[256] = {
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
  0x000100,
  0x000100,
  0x000100,
  0x000100,
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
  0x000200,
  0x000200,
  0x000200,
  0x000200,
  0x010200,
  0x010200,
  0x010200,
  0x010300,
  0x010300,
  0x010300,
  0x010300,
  0x010300,
  0x010300,
  0x010300,
  0x010300,
  0x010300,
  0x010400,
  0x010400,
  0x010400,
  0x010400,
  0x010400,
  0x010400,
  0x010400,
  0x010400,
  0x010500,
  0x010500,
  0x010500,
  0x020500,
  0x020500,
  0x020500,
  0x020500,
  0x020600,
  0x020600,
  0x020600,
  0x020600,
  0x020600,
  0x020600,
  0x020600,
  0x020600,
  0x020700,
  0x020700,
  0x020700,
  0x030700,
  0x030700,
  0x030700,
  0x030800,
  0x030800,
  0x030800,
  0x030800,
  0x030800,
  0x030800,
  0x030900,
  0x030900,
  0x040900,
  0x040900,
  0x040900,
  0x040900,
  0x040A00,
  0x040A01,
  0x040A01,
  0x040A01,
  0x050B01,
  0x050B01,
  0x050B01,
  0x050B01,
  0x050B01,
  0x050B01,
  0x050B01,
  0x050C01,
  0x060C01,
  0x060C01,
  0x060C01,
  0x060D01,
  0x060D01,
  0x060D01,
  0x060D01,
  0x060D01,
  0x070D01,
  0x070E01,
  0x070E01,
  0x070E01,
  0x070E01,
  0x070E01,
  0x080F02,
  0x080F02,
  0x080F02,
  0x080F02,
  0x081002,
  0x091002,
  0x091002,
  0x091002,
  0x091102,
  0x091102,
  0x091102,
  0x0A1102,
  0x0A1102,
  0x0A1202,
  0x0A1202,
  0x0B1203,
  0x0B1203,
  0x0B1303,
  0x0B1303,
  0x0B1303,
  0x0B1303,
  0x0C1403,
  0x0C1403,
  0x0C1403,
  0x0D1404,
  0x0D1404,
  0x0D1504,
  0x0D1504,
  0x0D1604,
  0x0D1604,
  0x0E1604,
  0x0E1605,
  0x0E1605,
  0x0E1705,
  0x0F1705,
  0x0F1705,
  0x0F1705,
  0x101805,
  0x101806,
  0x101806,
  0x101906,
  0x111906,
  0x111906,
  0x111906,
  0x111A07,
  0x121A07,
  0x121A07,
  0x121A07,
  0x131A07,
  0x131B08,
  0x131B08,
  0x131C08,
  0x141C08,
  0x141C09,
  0x141C09,
  0x141C09,
  0x151D09,
  0x161D0A,
  0x161E0A,
  0x161E0A,
  0x161E0B,
  0x171E0B,
  0x171E0B,
  0x171F0B,
  0x171F0C,
  0x18200C,
  0x19200C,
  0x19210D,
  0x19210D,
  0x19210D,
  0x1A210D,
  0x1A210E,
  0x1A220E,
  0x1A220F,
  0x1B220F,
  0x1C230F,
  0x1C2310,
  0x1C2310,
  0x1C2311,
  0x1D2411,
  0x1D2411,
  0x1E2412,
  0x1E2512,
  0x1E2513,
  0x1F2613,
  0x1F2613,
  0x202614,
  0x202714,
  0x212715,
  0x212716,
  0x212716,
  0x222817,
  0x222817,
  0x232817,
  0x232918,
  0x232919,
  0x242A19,
  0x242A1A,
  0x252A1A,
  0x252B1B,
  0x262B1C,
  0x272B1C,
  0x272B1D,
  0x272B1D,
  0x272C1E,
  0x282C1E,
  0x282D1F,
  0x292D20,
  0x2A2E21,
  0x2A2E21,
  0x2B2E22,
  0x2B2F23,
  0x2B2F23,
  0x2C3024,
  0x2C3025,
  0x2D3026,
  0x2D3127,
  0x2E3127,
  0x2E3128,
  0x2F3129,
  0x30312A,
  0x30322B,
  0x31322B,
  0x31332C,
  0x31332D,
  0x32332E,
  0x32342F,
  0x333430,
  0x333531,
  0x343532,
  0x353533,
  0x353634,
  0x363635,
  0x363736,
  0x373737
};
