// Вспышки

void Lighting() {
  for (int n = 0; n < 6; ++n) {
    int c = 255;
    for (int i = 0; i < 9; ++i) {
      one_color_all(c, c, c);
      LEDS.show();
      delay(20);
      c >>= 1;
    }
    delay(300);
  }
}
