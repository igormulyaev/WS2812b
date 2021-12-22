#ifndef M_LED_EFFECT_H
#define M_LED_EFFECT_H


// Basic Class for LED effects

class ITimer;

class LedEffect {
  public:
    virtual ~LedEffect() {};

    virtual void OnStart(ITimer* timer) = 0;
    virtual void OnInteract(const void* data) = 0;
    virtual void OnTimer() = 0;
    virtual const char* getName() const = 0;
};

#endif
