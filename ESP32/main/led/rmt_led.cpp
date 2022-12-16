#include "rmt_led.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_base.h"

#define LED_RMT_RESOLUTION_HZ (20 * 1000 * 1000)
#define LED_RMT_BLOCK_SYMBOLS 512
#define LED_RMT_QUEUE_DEPTH 4
#define LED_RMT_WITH_DMA 0

#define WS2812_T0H_NS 400.0
#define WS2812_T0L_NS 850.0
#define WS2812_T1H_NS 800.0
#define WS2812_T1L_NS 450.0

#define WS2812_MSB_FIRST 1

// ########################################################
// ### Constructor
// ########################################################
RmtLed :: RmtLed () :
  txChannel (NULL), txEncoder (NULL)
{
  ESP_LOGI (tag, "Init start");
  
  // ----------------------------------------------------------------
  ESP_LOGI (tag, "Install RMT TX channel");
  rmt_tx_channel_config_t cfgChannel = {
    .gpio_num = LED_RMT_TX_GPIO,
    .clk_src = RMT_CLK_SRC_DEFAULT,
    .resolution_hz = LED_RMT_RESOLUTION_HZ,
    .mem_block_symbols = LED_RMT_BLOCK_SYMBOLS,
    .trans_queue_depth = LED_RMT_QUEUE_DEPTH,
    .flags = {
      .invert_out = 0,
      .with_dma = LED_RMT_WITH_DMA,
      .io_loop_back = 0,
      .io_od_mode = 0,
    },
  };
  ESP_ERROR_CHECK (rmt_new_tx_channel (&cfgChannel, &txChannel));

  // ----------------------------------------------------------------
  ESP_LOGI (tag, "Init RMT encoder");
  rmt_bytes_encoder_config_t cfgEncoder = {
    .bit0 = {
      .duration0 = int (WS2812_T0H_NS / 1e9 * LED_RMT_RESOLUTION_HZ),
      .level0 = 1,
      .duration1 = int (WS2812_T0L_NS / 1e9 * LED_RMT_RESOLUTION_HZ),
      .level1 = 0,
    },
    .bit1 = {
      .duration0 = int (WS2812_T1H_NS / 1e9 * LED_RMT_RESOLUTION_HZ),
      .level0 = 1,
      .duration1 = int (WS2812_T1L_NS / 1e9 * LED_RMT_RESOLUTION_HZ),
      .level1 = 0,
    },
    .flags = {
      .msb_first = WS2812_MSB_FIRST
    }
  };
  ESP_ERROR_CHECK (rmt_new_bytes_encoder (&cfgEncoder, &txEncoder));

  // ----------------------------------------------------------------
  ESP_LOGI (tag, "Enable RMT");
  ESP_ERROR_CHECK (rmt_enable (txChannel));

  ESP_LOGI (tag, "Init end");
}

// ########################################################
// ### Destructor
// ########################################################
RmtLed :: ~RmtLed () 
{
  ESP_ERROR_CHECK (rmt_disable (txChannel));
  ESP_ERROR_CHECK (rmt_del_encoder (txEncoder));
  ESP_ERROR_CHECK (rmt_del_channel (txChannel));
}

// ########################################################
// ### Refresh LEDs
// ########################################################
void RmtLed :: refresh () 
{
  rmt_transmit_config_t cfgTransmit = {
    .loop_count = 0,
    .flags = {
      .eot_level = 0,
    }
  };
  esp_err_t ret = ESP_OK;

  ret = rmt_transmit (txChannel, txEncoder, leds, sizeof(leds), &cfgTransmit);
  
  if (ret != ESP_OK) {
    ESP_LOGE (tag, "transmit RMT samples failed: %d", ret);
  }
  else {
    rmt_tx_wait_all_done(txChannel, 50);
  }
}

// ########################################################
// ### Static constants
// ########################################################
const char * const RmtLed :: tag = "rmt_led";

