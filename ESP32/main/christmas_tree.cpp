#include "christmas_tree.h"
#include "led_params.h"

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
  M_TREE_CL_LIGHT1 | (1 - 1),
  M_TREE_CL_SPACE  | (1 - 1),
  M_TREE_CL_LIGHT1 | (1 - 1),
  M_TREE_CL_BRANCH | (6 - 1),
  M_TREE_CL_SPACE  | (2 - 1),
  M_TREE_CL_BRANCH | (6 - 1),
  M_TREE_CL_SPACE  | (1 - 1),
  M_TREE_CL_BRANCH | (7 - 1),
  M_TREE_CL_SPACE  | (2 - 1),
  M_TREE_CL_SNOW   | (4 - 1),
  // 7 col (reverse)
  M_TREE_CL_STEM   | (25 - 1),
  M_TREE_CL_LIGHT1 | (3 + 3 - 1),
  // 8 col
  M_TREE_CL_STEM   | (25 - 1),
  M_TREE_CL_SNOW   | (4 - 1),
  // 9 col (reverse)
  M_TREE_CL_SPACE  | (2 - 1),
  M_TREE_CL_BRANCH | (7 - 1),
  M_TREE_CL_SPACE  | (1 - 1),
  M_TREE_CL_BRANCH | (6 - 1),
  M_TREE_CL_SPACE  | (2 - 1),
  M_TREE_CL_BRANCH | (6 - 1),
  M_TREE_CL_LIGHT1 | (1 - 1),
  M_TREE_CL_SPACE  | (1 - 1),
  M_TREE_CL_LIGHT1 | (1 - 1),
  M_TREE_CL_SPACE  | (1 + 6 - 1),
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
void CChristmasTree :: OnTimer() {
  FastLED.show();
};

// -----------------------------------------------------
void CChristmasTree :: OnStart() {

  int pos = 0;
  const uint8_t *arch = treeArch;

  for (int cnt = sizeof(treeArch) / sizeof(treeArch[0]); cnt; --cnt) {

    uint8_t c = *arch++;
    int color = CRGB::Black;

    switch (c & M_TREE_CL_MASK) {
      case M_TREE_CL_SPACE:
        color = CRGB::Black;
        break;
      case M_TREE_CL_SNOW:
        color = 0x404040;
        break;
      case M_TREE_CL_LIGHT0:
        color = 0x204000;
        break;
      case M_TREE_CL_LIGHT1:
        color = 0x006000;
        break;
      case M_TREE_CL_BRANCH:
        color = 0x400000;
        break;
      case M_TREE_CL_STEM:
        color = 0x080200;
        break;
    }
    for (int cnt = (c & M_TREE_CNT_MASK) + 1; cnt && pos < NUM_LEDS; --cnt, ++pos) {
      leds[pos] = CRGB(color);
    }
  }

  for (; pos < NUM_LEDS; ++pos) {
    leds[pos] = CRGB::Black;
  }
}

// -----------------------------------------------------
CChristmasTree :: ~CChristmasTree() {
}
