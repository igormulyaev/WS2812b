#ifndef M_STARS_H
#define M_STARS_H

// Target frames per second
#define STARS_FPS 50
#define STARS_PALETTE_LEN 12

typedef struct {
  int pos[2];
  int step[2];
} SStarsData;

void starsStart(void *pvParameters);

#endif
