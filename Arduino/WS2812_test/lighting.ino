// Вспышки

void lighting() {
  static const struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    int ms;
  } def[10] = {
    {255, 255, 255, 5}, 
    {140, 128, 128, 7}, 
    {73, 64, 64, 9}, 
    {40, 32, 32, 12}, 
    {24, 16, 16, 16}, 
    {16, 8, 8, 21}, 
    {10, 4, 4, 27}, 
    {6, 2, 2, 35}, 
    {3, 1, 1, 45}, 
    {1, 0, 0, 58}
  };

  for (int i = 0; i < 10; ++i) {
    one_color_all(def[i].r, def[i].g, def[i].b);
    LEDS.show();
    delay(def[i].ms);
  }
  one_color_all(0, 0, 0);
  LEDS.show();
}
