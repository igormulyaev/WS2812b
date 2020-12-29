#include "stripe_pos.h"
#include "led_params.h"

void CStripePosition::up(); {
  pos += to_down? -1: 1;
}

void CStripePosition::down(); {
  pos += to_down? 1: -1;
}

void CStripePosition::left(); {
  pos -= direction;
  direction = -direction;
}

void CStripePosition::right(); {
  pos += direction;
  direction = -direction;
}

