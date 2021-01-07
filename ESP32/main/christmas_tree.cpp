#include "christmas_tree.h"
#include "led_params.h"

static STreeData treeData;

// -----------------------------------------------------
// Compressed tree
// (3-bit pixel color type) | (count - 1)
// count max = 32
static const uint8_t treeArch[] = {
  // 0 col
  M_TREE_CL_SPACE  | (25 - 1),
  M_TREE_CL_LIGHT0 | (2 - 1),
  M_TREE_CL_SPACE  | (1 - 1),
  M_TREE_CL_SNOW   | (4 - 1),
  // 1 col (reverse)
  M_TREE_CL_SPACE  | (1 - 1),
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_BRANCH | (2 - 1),
  M_TREE_CL_SPACE  | (4 - 1),
  M_TREE_CL_LIGHT0 | (2 - 1),
  M_TREE_CL_SPACE  | (18 + 11 - 1),
  // 2 col
  M_TREE_CL_LIGHT0 | (2 - 1),
  M_TREE_CL_SPACE  | (4 - 1),
  M_TREE_CL_BRANCH | (2 - 1),
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_SPACE  | (4 - 1),
  M_TREE_CL_BRANCH | (2 - 1),
  M_TREE_CL_SPACE  | (2 - 1),
  M_TREE_CL_SNOW   | (4 - 1),
  // 3 col (reverse)
  M_TREE_CL_SPACE  | (2 - 1),
  M_TREE_CL_BRANCH | (2 - 1),
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_SPACE  | (4 - 1),
  M_TREE_CL_BRANCH | (2 - 1),
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_SPACE  | (3 - 1),
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_BRANCH | (2 - 1),
  M_TREE_CL_SPACE  | (10 + 8 - 1),
  // 4 col
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_BRANCH | (3 - 1),
  M_TREE_CL_SPACE  | (3 - 1),
  M_TREE_CL_BRANCH | (3 - 1),
  M_TREE_CL_SPACE  | (4 - 1),
  M_TREE_CL_BRANCH | (4 - 1),
  M_TREE_CL_SPACE  | (2 - 1),
  M_TREE_CL_SNOW   | (4 - 1),
  // 5 col (reverse)
  M_TREE_CL_SPACE  | (2 - 1),
  M_TREE_CL_BRANCH | (4 - 1),
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_SPACE  | (3 - 1),
  M_TREE_CL_BRANCH | (3 - 1),
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_SPACE  | (3 - 1),
  M_TREE_CL_BRANCH | (4 - 1),
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_SPACE  | (6 + 1 - 1),
  // 6 col
  M_TREE_CL_LIGHT1 | (2 - 1),
  M_TREE_CL_SPACE  | (1 - 1),
  M_TREE_CL_BRANCH | (6 - 1),
  M_TREE_CL_SPACE  | (2 - 1),
  M_TREE_CL_BRANCH | (6 - 1),
  M_TREE_CL_SPACE  | (1 - 1),
  M_TREE_CL_BRANCH | (7 - 1),
  M_TREE_CL_SPACE  | (2 - 1),
  M_TREE_CL_SNOW   | (4 - 1),
  // 7 col (reverse)
  M_TREE_CL_STEM   | (26 - 1),
  M_TREE_CL_LIGHT1 | (2 + 2 - 1),
  // 8 col
  M_TREE_CL_STEM   | (26 - 1),
  M_TREE_CL_SNOW   | (4 - 1),
  // 9 col (reverse)
  M_TREE_CL_SPACE  | (2 - 1),
  M_TREE_CL_BRANCH | (7 - 1),
  M_TREE_CL_SPACE  | (1 - 1),
  M_TREE_CL_BRANCH | (6 - 1),
  M_TREE_CL_SPACE  | (2 - 1),
  M_TREE_CL_BRANCH | (6 - 1),
  M_TREE_CL_SPACE  | (1 - 1),
  M_TREE_CL_LIGHT1 | (1 - 1),
  M_TREE_CL_SPACE  | (2 + 6 - 1),
  // 10 col
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_BRANCH | (4 - 1),
  M_TREE_CL_SPACE  | (3 - 1),
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_BRANCH | (3 - 1),
  M_TREE_CL_SPACE  | (3 - 1),
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_BRANCH | (4 - 1),
  M_TREE_CL_SPACE  | (2 - 1),
  M_TREE_CL_SNOW   | (4 - 1),
  // 11 col (reverse)
  M_TREE_CL_SPACE  | (2 - 1),
  M_TREE_CL_BRANCH | (4 - 1),
  M_TREE_CL_SPACE  | (4 - 1),
  M_TREE_CL_BRANCH | (3 - 1),
  M_TREE_CL_SPACE  | (3 - 1),
  M_TREE_CL_BRANCH | (3 - 1),
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_SPACE  | (8 + 10 - 1),
  // 12 col
  M_TREE_CL_BRANCH | (2 - 1),
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_SPACE  | (3 - 1),
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_BRANCH | (2 - 1),
  M_TREE_CL_SPACE  | (4 - 1),
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_BRANCH | (2 - 1),
  M_TREE_CL_SPACE  | (2 - 1),
  M_TREE_CL_SNOW   | (4 - 1),
  // 13 col (reverse)
  M_TREE_CL_SPACE  | (2 - 1),
  M_TREE_CL_BRANCH | (2 - 1),
  M_TREE_CL_SPACE  | (4 - 1),
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_BRANCH | (2 - 1),
  M_TREE_CL_SPACE  | (4 - 1),
  M_TREE_CL_LIGHT0 | (2 - 1),
  M_TREE_CL_SPACE  | (11 + 18 - 1),
  // 14 col
  M_TREE_CL_LIGHT0 | (2 - 1),
  M_TREE_CL_SPACE  | (4 - 1),
  M_TREE_CL_BRANCH | (2 - 1),
  M_TREE_CL_LIGHT0 | (1 - 1),
  M_TREE_CL_SPACE  | (1 - 1),
  M_TREE_CL_SNOW   | (4 - 1),
  // 15 col (reverse)
  M_TREE_CL_SPACE  | (1 - 1),
  M_TREE_CL_LIGHT0 | (2 - 1)
};

//--------------------------------------------------------
static void tree_callback (void *param) {

  //STreeData *td = (STreeData *)param;

  FastLED.show();

  // Prepare next round
};

// -----------------------------------------------------
void setNLeds (int &pos, CRGB color, int cnt) {
  int new_pos = pos;
  for (; cnt && new_pos < NUM_LEDS; --cnt, ++new_pos) {
    leds[new_pos] = color;
  }
  pos = new_pos;
}
// -----------------------------------------------------
void treeStart(void *pvParameters) {

  int pos = 0;
  const uint8_t *arch = treeArch;

  for (int cnt = sizeof(treeArch) / sizeof(treeArch[0]); cnt; --cnt) {
    uint8_t c = *arch++;
    int a_cnt = (c & M_TREE_CNT_MASK) + 1;

    switch (c & M_TREE_CL_MASK) {
      case M_TREE_CL_SPACE:
        setNLeds(pos, CRGB::Black, a_cnt);
        break;
      case M_TREE_CL_SNOW:
        setNLeds(pos, 0x404040, a_cnt);
        break;
      case M_TREE_CL_LIGHT0:
        setNLeds(pos, 0x204000, a_cnt);
        break;
      case M_TREE_CL_LIGHT1:
        setNLeds(pos, 0x006000, a_cnt);
        break;
      case M_TREE_CL_BRANCH:
        setNLeds(pos, 0x400000, a_cnt);
        break;
      case M_TREE_CL_STEM:
        setNLeds(pos, 0x080200, a_cnt);
        break;
    }
  }
  
  if (pos < NUM_LEDS) {
    setNLeds(pos, CRGB::Black, NUM_LEDS - pos);
  }
  
  esp_timer_create_args_t timer_create_args = {
      .callback = tree_callback,
      .arg = (void *) &treeData,
      .dispatch_method = ESP_TIMER_TASK,
      .name = "tree_timer"
    };

  esp_timer_handle_t timer_h;

  esp_timer_create(&timer_create_args, &timer_h);

  esp_timer_start_periodic(timer_h, 1000000L / CHRISTMAS_TREE_FPS);

  // loop task
  while (1) {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  };

}




