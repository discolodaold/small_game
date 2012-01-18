struct branch {
    float x1, y1, x2, y2;
    int child; // a negative number is a leaf
};

typedef struct branch node_t[(int)(512/sizeof(struct branch))];

node_t nodes[] = {
#include "mapnodes.h"
};

void map_rect_map(float x1, float y1, float x2, float y2, void (*fun)(unsigned int index)) {
}

