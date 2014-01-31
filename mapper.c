#include "nos.h"
#include "data.h"

struct model_set {
    char *name;
    size_t tiles;
    size_t *tile;
};

struct dodad {
    size_t base;
    float x, y, rotation;
};

size_t dodads;
struct dodad dodad;

int nos_init(void) {
    int i;
    for(i = 0; i < DATUM_NUM; ++i) {

    }
    return 0;
}

/*
 * +------+---------------------------------------------------------+
 * |      | command help                                current map |
 * | T    |                                                         |
 * | I    |                                                         |
 * | L    |                                                         |
 * | E    |                                                         |
 * | S    |                                                         |
 * | .    |                                                         |
 * | .    |                                                         |
 * | .    |                                                         |
 * |      |                                                         |
 * |      |                                                         |
 * |      |                                                         |
 * |      |                                                         |
 * |      |                                                         |
 * |      |                                                         |
 * |      |                                                         |
 * |      |                                                         |
 * |      | Up arrow selects different tile                         |
 * |      | Down arrow selects different tile                       |
 * |+----+| LClick drops a dodad                                    |
 * ||    || Right/Left arrow rotates                                |
 * |+----+| LDrag moves dodad                                       |
 * |      | RDrag moves camera                                      |
 * |      |                                                         |
 * +------+---------------------------------------------------------+
 *
 * commands:
 *
 * t: tileset - enter a text name to load
 * m: map - enter a map to load
 * i: item mode - shows all items to place
 */
int nos_frame(void) {
    return 0;
}

void nos_uninit(void) {
}

