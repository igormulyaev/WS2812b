#ifndef M_CHRISTMAS_TREE_H
#define M_CHRISTMAS_TREE_H

#include <cstdint>
#include <vector>
#include "led_effect.h"
#include "FastLED.h"

class ChristmasTreeEffect: public LedEffect 
{
  public:
    ChristmasTreeEffect() {}
    virtual ~ChristmasTreeEffect();

    virtual void OnStart(ITimer* timer);
    virtual void OnInteract(const void* data) {};
    virtual void OnTimer();
    virtual const char* getName() const;

    static const char* const name;

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
    static const char* TAG;
};

#endif
