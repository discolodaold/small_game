#include "data.h"

struct data game_data[DATUM_NUM] = {
#define DATUM(ENUM, NAME, KIND, ...) {.name = NAME, .kind = KIND, __VA_ARGS__},
#include "data.x"
#undef DATUM
};

