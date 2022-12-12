#ifndef RMT_LED_H
#define RMT_LED_H

#include <stdint.h>
#include "esp_attr.h"
#include "driver/rmt_tx.h"
#include "led_params.h"
#include "pixel.h"

class RmtLed {

  public:

    RmtLed ();
    ~RmtLed ();

    void refresh ();

  private:
    rmt_channel_handle_t txChannel;
    rmt_encoder_handle_t txEncoder;

    static const char * const tag;

    RmtLed (const RmtLed&) = delete;
    RmtLed& operator= (const RmtLed&) = delete;
};

#endif
