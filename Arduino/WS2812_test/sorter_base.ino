void init_sort(uint8_t *arr) {

  // заполняем значениями по порядку, чтобы гарантированно были все
  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    arr[i] = i;
  }

  // перемешиваем
  for (uint8_t i = 100; i; --i) {
    uint8_t p1, p2, t;
    p1 = random(LED_COUNT);
    p2 = random(LED_COUNT);
    t = arr[p1];
    arr[p1] = arr[p2];
    arr[p2] = t;
  }

  // и заполняем цвета пикселей
  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    leds[i].r = gamma65[58 - i * 2];
    leds[i].g = gamma65[29];
    leds[i].b = gamma65[i * 2];
  }
}
