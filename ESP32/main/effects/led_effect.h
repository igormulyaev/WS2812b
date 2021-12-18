#ifndef M_LED_EFFECT_H
#define M_LED_EFFECT_H

/*
  Basic Class for LED effects
*/
#define M_INTERACT_DATA_LENGHT 16

class ITimer;

class LedEffect {
  public:
    virtual void OnStart(ITimer* timer) = 0;
    virtual void OnInteract(const void* data) = 0;
    virtual void OnTimer() = 0;
    virtual ~LedEffect() {};
};

#endif
