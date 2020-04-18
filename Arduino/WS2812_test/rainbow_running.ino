//----------------------------------------------------------
int rainbowR(int pos) {
  return pos < 65? 65: (
    pos < 130? 130 - pos: (
      pos < 260? 0: (
        pos < 325? pos - 260: 
          65
      )
    )
  );
}

//----------------------------------------------------------
int rainbowG(int pos) {
  return pos < 65? pos: (
    pos < 195? 65: (
      pos < 260? 260 - pos: 
        0
    )
  );
}

//----------------------------------------------------------
int rainbowB(int pos) {
  return pos < 130? 0: (
    pos < 195? pos - 130: (
      pos < 325? 65:
        390 - pos
    )
  );
}

//----------------------------------------------------------
// одни проход радуги по ленте
void rainbowRunning(char type) {
  uint8_t ledSE = 0;
  uint8_t nextCnt = 13;

  for (int pos0 = 0; pos0 < 390; ++pos0) {
    int pos = pos0;
    for (uint8_t i = 0; i < LED_COUNT; ++i) {
      if (type == 'W' || (type == 'S' && i < ledSE) || (type == 'E' && i >= ledSE)) {
        leds[i].r = rainbowR(pos);
        leds[i].g = rainbowG(pos);
        leds[i].b = rainbowB(pos);
      }
      else {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
      }

      pos += 13;
      pos = pos >= 390? pos - 390: pos;
    }
    LEDS.show();

    if (--nextCnt == 0) {
      nextCnt = 13;
      ++ledSE;
    }

    delay(7);
  }
}
