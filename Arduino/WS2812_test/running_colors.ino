void runningColors() {
  static const CRGB modes[7] = {{0, 255, 0}, {255, 0, 0}, {0, 0, 255}, {128, 0, 128}, {0, 128, 128}, {128, 128, 0}, {85, 85, 85}};

  for (int mode = 0; mode <= 6; ++mode) {

    for (int i = 0; i < LED_COUNT; ++i) {
      leds[i] = modes[mode];
      LEDS.show();
      delay(50);

      leds[i].setRGB(0, 0, 0);
    }
  }

  LEDS.show();
}
