// Пауза между шагами алгоритмов
static const unsigned int ledsort_step_delay = 70;

// заполняем значениями по порядку, чтобы гарантированно были все
void ledsort_init_sorted (uint8_t *arr) {

  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    arr[i] = i;
  }
}

// перемешиваем
void ledsort_shuffle (uint8_t *arr) {

  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    uint8_t j, t;
    j = random(LED_COUNT);
    t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
  }
}

// заполняем цвета пикселей
void ledsort_set_led (uint8_t *arr) {

  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    uint8_t v = arr[i];
    v = (v << 1) + (v >> 2); // 0..29 -> 0..65
    leds[i].r = gamma65[65 - v];
    leds[i].g = gamma65[v];
    leds[i].b = 0;
  }
}

// Обмен двух значений в массиве и цветов соответствующих LED
void ledsort_swap (uint8_t *arr, uint8_t pos) {
  uint8_t t = arr[pos];
  arr[pos] = arr[pos + 1];
  arr[pos + 1] = t;

  CRGB tt = leds[pos];
  leds[pos] = leds[pos + 1];
  leds[pos + 1] = tt;
}

// перебивка черным - вывод - пауза
void ledsort_show (uint8_t *arr, unsigned int show_time) {
  one_color_all (0, 0, 0);
  LEDS.show();

  delay (100);

  ledsort_set_led (arr);
  LEDS.show();

  if (show_time != 0) {
    delay (show_time);
  }
}
