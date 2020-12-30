#include "stars.h"
#include "led_params.h"

static SStarsData starsData;

static CRGB starsPalette[STARS_STEPS] = {
  0x4B5C38,
  0x809764,
  0xA6BD87,
  0xC0D5A1,
  0xD3E4B6,
  0xE0EEC6,
  0xE9F4D3,
  0xEFF8DC,
  0xF4FBE4,
  0xF7FCEA,
  0xFAFDEF,
  0xFBFEF2,
  0xFCFEF5,
  0xFDFFF7,
  0xFEFFF9,
  0xFEFFFA,
  0xFEFFFB,
  0xFFFFFC,
  0xFFFFFD,
  0xFFFFFD,
  0xFFFFFF,
  0xE1E7D9,
  0xC6D0B8,
  0xAEBC9C,
  0x99AA85,
  0x879A71,
  0x778B60,
  0x697E51,
  0x5C7245,
  0x51673A,
  0x475D32,
  0x3F542A,
  0x374C24,
  0x31451E,
  0x2B3E1A,
  0x263816,
  0x213313,
  0x1D2E10,
  0x1A290D,
  0x17250B,
  0x14220A,
  0x121F08,
  0x101C07,
  0x0E1906,
  0x0C1705,
  0x0B1404,
  0x091204,
  0x081103,
  0x070F03,
  0x060E02,
  0x060C02,
  0x050B02,
  0x040A01,
  0x040901,
  0x030801,
  0x030701,
  0x030701,
  0x020601,
  0x020601,
  0x020500,
  0x020500,
  0x010400,
  0x010400,
  0x010300,
  0x010300,
  0x010300,
  0x010200,
  0x010200,
  0x010200,
  0x000200,
  0x000200,
  0x000100,
  0x000100,
  0x000100,
  0x000100
};

//--------------------------------------------------------
static void stars_callback (void *param) {

  SStarsData *sd = (SStarsData *)param;
  int *pos = sd->pos;
  int *step = sd->step;

  // Update colors for current stars
  for (int starN = 0; starN < STARS_COUNT; ++starN) {
    leds[pos[starN]] = starsPalette[step[starN]];
  }

  FastLED.show();

  // Prepare next round
  for (int starN = 0; starN < STARS_COUNT; ++starN) {
    if (++step[starN] == STARS_STEPS) {
      leds[pos[starN]] = CRGB::Black;
      pos[starN] = esp_random() % NUM_LEDS;
      step[starN] = 0;
    }
  }
};

//--------------------------------------------------------
void starsStart (void *pvParameters) {

  for (int starN = 0; starN < STARS_COUNT; ++starN) {
    starsData.pos[starN] = esp_random() % NUM_LEDS;
    starsData.step[starN] = starN * STARS_STEPS / STARS_COUNT;
  }

  esp_timer_create_args_t timer_create_args = {
      .callback = stars_callback,
      .arg = (void *) &starsData,
      .dispatch_method = ESP_TIMER_TASK,
      .name = "stars_timer"
    };

  esp_timer_handle_t timer_h;

  esp_timer_create(&timer_create_args, &timer_h);

  esp_timer_start_periodic(timer_h, 1000000L / STARS_FPS);

  // loop task
  while (1) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  };

}
