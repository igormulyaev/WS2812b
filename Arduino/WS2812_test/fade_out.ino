void fadeOut() {
  int d = 20;
  for (int j = 0; j < 8; ++j) {
    for (int i = 0; i < LED_COUNT; i++ ) {
      leds[i].r >>= 1;
      leds[i].g >>= 1;
      leds[i].b >>= 1;
    }
    LEDS.show();
    delay(2000);
    d += 20;
  }
}
