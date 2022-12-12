#include "christmas_tree_effect.h"
#include "led/led_base.h"
#include "led/rmt_led.h"
#include "timer_interface.h"
#include "esp_random.h"
#include "esp_log.h"

// Refresh frequency, Hz
#define M_REFRESH_FREQ 50
// Black background
#define M_TREE_CL_SPACE (1 << 5)
// Sparks of snow
#define M_TREE_CL_SNOW (2 << 5)
// Light type 0 (on branches)
#define M_TREE_CL_LIGHT_BRANCH (3 << 5)
// Light type 1 (on top)
#define M_TREE_CL_LIGHT_TOP (4 << 5)
// Tree branch
#define M_TREE_CL_BRANCH (5 << 5)
// Tree stem
#define M_TREE_CL_STEM (6 << 5)

#define M_TREE_CL_MASK (7 << 5)
#define M_TREE_CNT_MASK 0x1f

#define M_BRANCH_COLOR 0x400000
#define M_STEM_COLOR   0x080200

// -----------------------------------------------------
// Compressed tree
// (3-bit pixel color type) | (count - 1)
// count max = 32
const uint8_t ChristmasTreeEffect :: treeArch[] = {
  // 0 col
  M_TREE_CL_SPACE        | (25 - 1),
  M_TREE_CL_LIGHT_BRANCH | (2 - 1),
  M_TREE_CL_SPACE        | (1 - 1),
  M_TREE_CL_SNOW         | (4 - 1),
  // 1 col (reverse)
  M_TREE_CL_SPACE        | (1 - 1),
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_BRANCH       | (2 - 1),
  M_TREE_CL_SPACE        | (4 - 1),
  M_TREE_CL_LIGHT_BRANCH | (2 - 1),
  M_TREE_CL_SPACE        | (18 + 11 - 1),
  // 2 col
  M_TREE_CL_LIGHT_BRANCH | (2 - 1),
  M_TREE_CL_SPACE        | (4 - 1),
  M_TREE_CL_BRANCH       | (2 - 1),
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_SPACE        | (4 - 1),
  M_TREE_CL_BRANCH       | (2 - 1),
  M_TREE_CL_SPACE        | (2 - 1),
  M_TREE_CL_SNOW         | (4 - 1),
  // 3 col (reverse)
  M_TREE_CL_SPACE        | (2 - 1),
  M_TREE_CL_BRANCH       | (2 - 1),
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_SPACE        | (4 - 1),
  M_TREE_CL_BRANCH       | (2 - 1),
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_SPACE        | (3 - 1),
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_BRANCH       | (2 - 1),
  M_TREE_CL_SPACE        | (10 + 8 - 1),
  // 4 col
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_BRANCH       | (3 - 1),
  M_TREE_CL_SPACE        | (3 - 1),
  M_TREE_CL_BRANCH       | (3 - 1),
  M_TREE_CL_SPACE        | (4 - 1),
  M_TREE_CL_BRANCH       | (4 - 1),
  M_TREE_CL_SPACE        | (2 - 1),
  M_TREE_CL_SNOW         | (4 - 1),
  // 5 col (reverse)
  M_TREE_CL_SPACE        | (2 - 1),
  M_TREE_CL_BRANCH       | (4 - 1),
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_SPACE        | (3 - 1),
  M_TREE_CL_BRANCH       | (3 - 1),
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_SPACE        | (3 - 1),
  M_TREE_CL_BRANCH       | (4 - 1),
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_SPACE        | (6 + 1 - 1),
  // 6 col
  M_TREE_CL_LIGHT_TOP    | (1 - 1),
  M_TREE_CL_SPACE        | (1 - 1),
  M_TREE_CL_LIGHT_TOP    | (1 - 1),
  M_TREE_CL_BRANCH       | (6 - 1),
  M_TREE_CL_SPACE        | (2 - 1),
  M_TREE_CL_BRANCH       | (6 - 1),
  M_TREE_CL_SPACE        | (1 - 1),
  M_TREE_CL_BRANCH       | (7 - 1),
  M_TREE_CL_SPACE        | (2 - 1),
  M_TREE_CL_SNOW         | (4 - 1),
  // 7 col (reverse)
  M_TREE_CL_STEM         | (25 - 1),
  M_TREE_CL_LIGHT_TOP    | (3 + 3 - 1),
  // 8 col
  M_TREE_CL_STEM         | (25 - 1),
  M_TREE_CL_SNOW         | (4 - 1),
  // 9 col (reverse)
  M_TREE_CL_SPACE        | (2 - 1),
  M_TREE_CL_BRANCH       | (7 - 1),
  M_TREE_CL_SPACE        | (1 - 1),
  M_TREE_CL_BRANCH       | (6 - 1),
  M_TREE_CL_SPACE        | (2 - 1),
  M_TREE_CL_BRANCH       | (6 - 1),
  M_TREE_CL_LIGHT_TOP    | (1 - 1),
  M_TREE_CL_SPACE        | (1 - 1),
  M_TREE_CL_LIGHT_TOP    | (1 - 1),
  M_TREE_CL_SPACE        | (1 + 6 - 1),
  // 10 col
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_BRANCH       | (4 - 1),
  M_TREE_CL_SPACE        | (3 - 1),
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_BRANCH       | (3 - 1),
  M_TREE_CL_SPACE        | (3 - 1),
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_BRANCH       | (4 - 1),
  M_TREE_CL_SPACE        | (2 - 1),
  M_TREE_CL_SNOW         | (4 - 1),
  // 11 col (reverse)
  M_TREE_CL_SPACE        | (2 - 1),
  M_TREE_CL_BRANCH       | (4 - 1),
  M_TREE_CL_SPACE        | (4 - 1),
  M_TREE_CL_BRANCH       | (3 - 1),
  M_TREE_CL_SPACE        | (3 - 1),
  M_TREE_CL_BRANCH       | (3 - 1),
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_SPACE        | (8 + 10 - 1),
  // 12 col
  M_TREE_CL_BRANCH       | (2 - 1),
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_SPACE        | (3 - 1),
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_BRANCH       | (2 - 1),
  M_TREE_CL_SPACE        | (4 - 1),
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_BRANCH       | (2 - 1),
  M_TREE_CL_SPACE        | (2 - 1),
  M_TREE_CL_SNOW         | (4 - 1),
  // 13 col (reverse)
  M_TREE_CL_SPACE        | (2 - 1),
  M_TREE_CL_BRANCH       | (2 - 1),
  M_TREE_CL_SPACE        | (4 - 1),
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_BRANCH       | (2 - 1),
  M_TREE_CL_SPACE        | (4 - 1),
  M_TREE_CL_LIGHT_BRANCH | (2 - 1),
  M_TREE_CL_SPACE        | (11 + 18 - 1),
  // 14 col
  M_TREE_CL_LIGHT_BRANCH | (2 - 1),
  M_TREE_CL_SPACE        | (4 - 1),
  M_TREE_CL_BRANCH       | (2 - 1),
  M_TREE_CL_LIGHT_BRANCH | (1 - 1),
  M_TREE_CL_SPACE        | (1 - 1),
  M_TREE_CL_SNOW         | (4 - 1),
  // 15 col (reverse)
  M_TREE_CL_SPACE        | (1 - 1),
  M_TREE_CL_LIGHT_BRANCH | (2 - 1)
};

// -----------------------------------------------------
const RGB ChristmasTreeEffect :: snowPalette[] = {
  0x010101,
  0x010101,
  0x010101,
  0x020202,
  0x020202,
  0x020202,
  0x030303,
  0x030303,
  0x030303,
  0x040404,
  0x040404,
  0x050505,
  0x050505,
  0x060606,
  0x060606,
  0x070707,
  0x080808,
  0x080808,
  0x090909,
  0x0A0A0A,
  0x0B0B0B,
  0x0B0B0B,
  0x0C0C0C,
  0x0D0D0D,
  0x0E0E0E,
  0x0F0F0F
};

// -----------------------------------------------------
const RGB ChristmasTreeEffect :: lightBranchPalette[] = {
  0x001300,
  0x001400,
  0x001500,
  0x001600,
  0x011700,
  0x011900,
  0x011A00,
  0x021B00,
  0x031C00,
  0x031E00,
  0x041F00,
  0x052100,
  0x062200,
  0x082300,
  0x092500,
  0x0B2700,
  0x0C2800,
  0x0E2A00,
  0x102B00,
  0x122D00,
  0x142F00,
  0x163100,
  0x193200,
  0x1B3400,
  0x1E3600,
  0x213800
};

// -----------------------------------------------------
const RGB ChristmasTreeEffect :: lightTopPalette[] = {
  0x000300,
  0x000300,
  0x000300,
  0x000400,
  0x000400,
  0x000500,
  0x000500,
  0x000600,
  0x000600,
  0x000700,
  0x000800,
  0x000800,
  0x000900,
  0x000A00,
  0x000B00,
  0x000B00,
  0x000C00,
  0x000D00,
  0x000E00,
  0x000F00,
  0x001000,
  0x001100,
  0x001200,
  0x001300,
  0x001400,
  0x001500,
  0x001600,
  0x001700,
  0x001900,
  0x001A00,
  0x001B00,
  0x001C00,
  0x001E00,
  0x001F00,
  0x002100,
  0x002200,
  0x002300,
  0x002500,
  0x002700,
  0x002800,
  0x002A00,
  0x002B00,
  0x002D00,
  0x002F00,
  0x003100,
  0x003200,
  0x003400,
  0x003600,
  0x003800,
  0x003A00
};

// -----------------------------------------------------
const char* const ChristmasTreeEffect :: TAG = "christmas_tree_effect";

const char* const ChristmasTreeEffect :: name = "ChristmasTree";

// -----------------------------------------------------
const char* ChristmasTreeEffect :: getName() const
{
  return name;
}

// -----------------------------------------------------
void ChristmasTreeEffect :: updatePixels (std :: vector <ChristmasTreeEffect :: SEffectPixel> &vec, const RGB *palette, int paletteSize) 
{
  for (auto p = vec.begin(); p != vec.end(); ++p) {
    leds[p->ledIndex] = palette[p->curColorIndex];

    if (p->curColorIndex == p->tgtColorIndex) {
      p->tgtColorIndex = esp_random() % paletteSize;
    }
    else {
      p->curColorIndex += (p->curColorIndex < p->tgtColorIndex)? 1: -1;
    }
  }
}

// -----------------------------------------------------
void ChristmasTreeEffect :: OnTimer() 
{
  rmtLed -> refresh ();
  // update dynamic pixels

  // top light
  for (auto p = lightTopVec.begin(); p != lightTopVec.end(); ++p) {
    leds[*p] = lightTopPalette[lightTopCurColorIndex];
  }

  if (lightTopCurColorIndex == lightTopTgtColorIndex) {
    lightTopTgtColorIndex = esp_random() % (sizeof(lightTopPalette) / sizeof(lightTopPalette[0]));
  }
  else {
    lightTopCurColorIndex += (lightTopCurColorIndex < lightTopTgtColorIndex)? 1: -1;
  }

  // snow
  updatePixels(snowVec, snowPalette, sizeof(snowPalette) / sizeof(snowPalette[0]));

  // branch lights
  updatePixels(lightBranchVec, lightBranchPalette, sizeof(lightBranchPalette) / sizeof(lightBranchPalette[0]));

};

// -----------------------------------------------------
void ChristmasTreeEffect :: OnStart (ITimer* timer)
{
  ESP_LOGI(TAG, "Start");

  snowVec.reserve(32);
  lightBranchVec.reserve(30);
  lightTopVec.reserve(8);

  lightTopCurColorIndex = 0;
  lightTopTgtColorIndex = 0;

  int pos = 0;
  const uint8_t *arch = treeArch;

  for (int cnt = sizeof(treeArch) / sizeof(treeArch[0]); cnt; --cnt) {

    uint8_t c = *arch++;
    uint8_t cType = c & M_TREE_CL_MASK;

    for (int cnt = (c & M_TREE_CNT_MASK) + 1; cnt && pos < LED_COUNT; --cnt, ++pos) {
      switch (cType) {
        case M_TREE_CL_SPACE:
          leds[pos] = RGB::Black;
          break;
        case M_TREE_CL_SNOW:
          leds[pos] = snowPalette[0];
          snowVec.push_back( {
            .ledIndex = pos, 
            .curColorIndex = 0, 
            .tgtColorIndex = 0
          });
          break;
        case M_TREE_CL_LIGHT_BRANCH:
          leds[pos] = lightBranchPalette[0];
          lightBranchVec.push_back( {
            .ledIndex = pos, 
            .curColorIndex = 0, 
            .tgtColorIndex = 0
          });
          break;
        case M_TREE_CL_LIGHT_TOP:
          leds[pos] = lightTopPalette[0];
          lightTopVec.push_back(pos);
          break;
        case M_TREE_CL_BRANCH:
          leds[pos] = M_BRANCH_COLOR;
          break;
        case M_TREE_CL_STEM:
          leds[pos] = M_STEM_COLOR;
          break;
      }
    }
  }

  for (; pos < LED_COUNT; ++pos) {
    leds[pos] = RGB::Black;
  }

  timer -> startTimer (1000000 / M_REFRESH_FREQ);
}

// -----------------------------------------------------
ChristmasTreeEffect :: ~ChristmasTreeEffect() 
{
}
