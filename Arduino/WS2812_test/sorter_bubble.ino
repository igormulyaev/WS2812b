void ledsort_bubble(uint8_t *arr) {
  bool cont = false;
  uint8_t endPos = LED_COUNT - 1;

  do {
    cont = false;
    for (uint8_t i = 0; i < endPos; ++i) {
      if (arr[i] > arr[i + 1]) {
        uint8_t t = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = t;

        CRGB tt = leds[i];
        leds[i] = leds[i + 1];
        leds[i + 1] = tt;

        cont = true;

        LEDS.show();
      }
      delay(ledsort_step_delay);
    }
    --endPos;
  } while (cont);
}
