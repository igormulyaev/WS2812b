#include "FastLED.h"          // библиотека для работы с лентой

#define LED_COUNT 30          // число светодиодов в кольце/ленте
#define LED_DT 13             // пин, куда подключен DIN ленты

int max_bright = 255;         // максимальная яркость (0 - 255)

// ---------------СЛУЖЕБНЫЕ ПЕРЕМЕННЫЕ-----------------
struct CRGB leds[LED_COUNT];

//----------------------------------------------------------
void one_color_all(uint8_t cred, uint8_t cgrn, uint8_t cblu) {       //-SET ALL LEDS TO ONE COLOR
  for (int i = 0 ; i < LED_COUNT; i++ ) {
    leds[i].setRGB( cred, cgrn, cblu);
  }
}

//----------------------------------------------------------
void setup()
{
  LEDS.setBrightness(max_bright);  // ограничить максимальную яркость

  LEDS.addLeds<WS2811, LED_DT, GRB>(leds, LED_COUNT);  // настрйоки для нашей ленты (ленты на WS2811, WS2812, WS2812B)
  one_color_all(0, 0, 0);          // погасить все светодиоды
  LEDS.show();                     // отослать команду
}

//----------------------------------------------------------
// Бегущий огонь
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

//----------------------------------------------------------
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

//----------------------------------------------------------
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
void rainbowRunning() {
  for (int pos0 = 0; pos0 < 390; ++pos0) {
    int pos = pos0;
    for (int i = 0; i < LED_COUNT; ++i) {
      leds[i].r = rainbowR(pos);
      leds[i].g = rainbowG(pos);
      leds[i].b = rainbowB(pos);
      pos += 13;
      pos = pos >= 390? pos - 390: pos;
    }
    LEDS.show();
    delay(5);
  }
}
//----------------------------------------------------------
void loop() {
  /*runningColors();

  delay(3000);

  Lighting();

  delay(2000);*/

  // rainbowInTime();
  // delay(64 * 30);
  //delay(2000);

  rainbowRunning();

}
