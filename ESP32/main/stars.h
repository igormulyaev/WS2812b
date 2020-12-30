#ifndef M_STARS_H
#define M_STARS_H

// Target frames per second
#define STARS_FPS 50
#define STARS_STEPS 75
#define STARS_COUNT 10

typedef struct {
  int pos[STARS_COUNT];
  int step[STARS_COUNT];
} SStarsData;

void starsStart(void *pvParameters);

#endif
