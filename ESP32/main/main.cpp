/* 
   This code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "led_params.h"

#include "FastLED.h"
#include "FX.h"

#define GPIO_INPUT_IO_0     GPIO_NUM_0
#define GPIO_INPUT_PIN_SEL  (1ULL<<GPIO_INPUT_IO_0)
#define ESP_INTR_FLAG_DEFAULT 0

extern "C" {
  void app_main();
}

CRGB leds[NUM_LEDS];

static xQueueHandle gpio_evt_queue = NULL;

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

static void gpio_task_example(void* arg)
{
}


void app_main() {
  /*
  gpio_config_t io_conf;

  //interrupt of rising edge
  io_conf.intr_type = GPIO_INTR_POSEDGE;
  //bit mask of the pins, use GPIO4/5 here
  io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
  //set as input mode    
  io_conf.mode = GPIO_MODE_INPUT;
  //enable pull-up mode
  io_conf.pull_up_en = GPIO_PULLUP_ENABLE;

  gpio_config(&io_conf);

  //create a queue to handle gpio event from isr
  gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
  //start gpio task
  xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);

  //install gpio isr service
  gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
  //hook isr handler for specific gpio pin
  gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void*) GPIO_INPUT_IO_0);
    */
  printf(" entering app main, call add leds\n");
  // the WS2811 family uses the RMT driver
  FastLED.addLeds<LED_TYPE, LED_DATA_PIN>(leds, NUM_LEDS);

  FastLED.clearData();
  FastLED.show();
  
  int pos = NUM_LEDS - 1;

  while(1) {
    vTaskDelay(50 / portTICK_PERIOD_MS);
    printf("set %d black\n", pos);
    leds[pos].setRGB(0, 0, 0);
    
    pos = (pos + 1) % NUM_LEDS;
    printf("set %d white\n", pos);
    leds[pos].setRGB(32, 32, 32);
    FastLED.show();
  };

}
