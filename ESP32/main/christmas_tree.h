#ifndef M_CHRISTMAS_TREE_H
#define M_CHRISTMAS_TREE_H

// Target frames per second
#define CHRISTMAS_TREE_FPS 50

// Black background
#define M_TREE_CL_SPACE (1 << 5)
// Sparks of snow
#define M_TREE_CL_SNOW (2 << 5)
// Light type 0 (on branches)
#define M_TREE_CL_LIGHT0 (3 << 5)
// Light type 1 (on top)
#define M_TREE_CL_LIGHT1 (4 << 5)
// Tree branch
#define M_TREE_CL_BRANCH (5 << 5)
// Tree stem
#define M_TREE_CL_STEM (6 << 5)

#define M_TREE_CL_MASK (7 << 5)
#define M_TREE_CNT_MASK 0x1f

typedef struct {
  int dummy;
} STreeData;

void treeStart(void *pvParameters);

#endif
