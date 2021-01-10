#ifndef M_LED_EFFECT_H
#define M_LED_EFFECT_H

/*
  Basic Class for LED effects
*/

class CLedEffect {
  public:
    virtual void OnStart() = 0;
    virtual void OnTimer() = 0;
    virtual ~CLedEffect() {};
};

#endif
