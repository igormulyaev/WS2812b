void ledsort_quick(uint8_t *arr, uint8_t low, uint8_t high) {
  uint8_t v = arr [(low + high) / 2];
  uint8_t i = low;
  uint8_t j = high;
  bool cont = false;

  while (i < j) {
    while (i < j && arr [i] < v) {
      ++ i;
      delay(ledsort_step_delay);
    }

    while (i < j && arr [j] >= v) {
      -- j;
      delay(ledsort_step_delay);
    }

    if (i < j) {
      uint8_t t = arr[i];
      arr[i] = arr[j];
      arr[j] = t;

      CRGB tt = leds[i];
      leds[i] = leds[j];
      leds[j] = tt;

      cont = true;
      ++ i;
      -- j;

      LEDS.show();

      delay(ledsort_step_delay);
    }
  } 
  if (cont) {
  }
}
