static const int ledsort_step_delay = 70;

// заполняем значениями по порядку, чтобы гарантированно были все
void ledsort_init_sorted(uint8_t *arr) {

  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    arr[i] = i;
  }
}

// перемешиваем
void ledsort_shuffle(uint8_t *arr) {

  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    uint8_t j, t;
    j = random(LED_COUNT);
    t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
  }
}

// заполняем цвета пикселей
void ledsort_set_led(uint8_t *arr) {

  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    uint8_t v = arr[i];
    v = (v << 1) + (v >> 2); // 0..29 -> 0..65
    leds[i].r = gamma65[65 - v];
    leds[i].g = gamma65[v];
    leds[i].b = 0;
  }
}
