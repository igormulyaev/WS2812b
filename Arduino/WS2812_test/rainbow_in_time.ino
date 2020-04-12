// Радуга по времени
void rainbowInTime() {
  CRGB c = {0, 0, 0};
  for (int mode = 0; mode < 6; ++mode) {
    for (int i = 0; i < 64; ++i) {
      switch (mode) {
        case 0:
          ++c.r;
          break;
        case 1:
          ++c.g;
          break;
        case 2:
          --c.r;
          break;
        case 3:
          ++c.b;
          break;
        case 4:
          --c.g;
          break;
        case 5:
          --c.b;
          break;
      }
      one_color_all(c.r, c.g, c.b);
      LEDS.show();
      delay(30);
    }
  }
}
