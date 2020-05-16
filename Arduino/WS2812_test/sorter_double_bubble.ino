void ledsort_double_bubble(uint8_t *arr) {
  uint8_t startPos = 0;
  uint8_t endPos = LED_COUNT - 1;

  do {
    bool cont = false;
    for (uint8_t i = startPos; i < endPos; ++i) {
      if (arr[i] > arr[i + 1]) {
        ledsort_swap(arr, i);

        cont = true;

        LEDS.show();
      }
      delay(ledsort_step_delay);
    }
    if (!cont) {
      break;
    }
    --endPos;

    cont = false;

    for (uint8_t i = endPos; i > startPos; --i) {
      if (arr[i - 1] > arr[i]) {
        ledsort_swap(arr, i - 1);

        cont = true;

        LEDS.show();
      }
      delay(ledsort_step_delay);
    }
    if (!cont) {
      break;
    }
    ++startPos;
  } while (true);
}
