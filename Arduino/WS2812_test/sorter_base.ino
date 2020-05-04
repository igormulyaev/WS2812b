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
    leds[i].r = gamma65[58 - arr[i] * 2];
    leds[i].g = gamma65[29];
    leds[i].b = gamma65[arr[i] * 2];
  }
}
