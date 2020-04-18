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

  LEDS.addLeds<WS2811, LED_DT, GRB>(leds, LED_COUNT);  // настройки для нашей ленты (ленты на WS2811, WS2812, WS2812B)
  one_color_all(0, 0, 0);          // погасить все светодиоды
  LEDS.show();                     // отослать команду
}

//----------------------------------------------------------
void loop() {
  rainbowRunning('S');
  for (int i = 0; i < 6; ++i) {
    rainbowRunning('W');
  }
  rainbowRunning('E');

  delay(2000);

  lighting();

  delay(2000);
}
