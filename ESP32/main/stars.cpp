#include "stars.h"
#include "led_params.h"

static SStarsData starsData;

static CRGB starsPalette[STARS_PALETTE_LEN] = {
  0x808080,
  0xffffff,
  0x868680,
  0x464630,
  0x252505,
  0x111300,
  0x030a00,
  0x010500,
  0x000300,
  0x000200,
  0x000100,
  0x000100
};

//--------------------------------------------------------
static void stars_callback (void *param) {

  SStarsData *sd = (SStarsData *)param;

  leds[sd->pos[0]] = starsPalette[sd->step[0]];

  if (sd->step[1] >= 0) {
    leds[sd->pos[1]] = starsPalette[sd->step[1]];
  }

  FastLED.show();

  switch (++(sd->step[0])) {
    case 7:
      // run second star
      sd->pos[1] = esp_random() % NUM_LEDS;
      sd->step[1] = 0;
      break;
    case STARS_PALETTE_LEN:
      // first star ends, move second to first
      leds[sd->pos[0]] = CRGB::Black;
      sd->pos[0] = sd->pos[1];
      sd->step[0] = sd->step[1];
      sd->step[1] = -1;
      break;
  }

};

//--------------------------------------------------------
void starsStart (void *pvParameters) {

  starsData.pos[0] = 0;
  starsData.pos[1] = 0;
  starsData.step[0] = 0;
  starsData.step[1] = -1;

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
