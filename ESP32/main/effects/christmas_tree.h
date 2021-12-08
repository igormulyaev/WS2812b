#ifndef M_CHRISTMAS_TREE_H
#define M_CHRISTMAS_TREE_H

#include <cstdint>
#include <vector>
#include "led_effect.h"
#include "FastLED.h"

class CChristmasTree: public CLedEffect {
  private:
    static const uint8_t treeArch[];
    static const CRGB snowPalette[];
    static const CRGB lightBranchPalette[];
    static const CRGB lightTopPalette[];

    struct SEffectPixel {
      int ledIndex;
      int curColorIndex;
      int tgtColorIndex;
    };

    std :: vector <SEffectPixel> snowVec;
    std :: vector <SEffectPixel> lightBranchVec;
    std :: vector <int> lightTopVec;

    int lightTopCurColorIndex;
    int lightTopTgtColorIndex;

    static void updatePixels(std :: vector <SEffectPixel> &vec, const CRGB *palette, int paletteSize);

  public:
    virtual void OnStart();
    virtual void OnTimer();
    virtual ~CChristmasTree();
};
#endif
