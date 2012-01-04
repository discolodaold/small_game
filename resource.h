#ifndef RESOURCE_H
#define RESOURCE_H

#include <stdlib.h>

void resource_init(void);
void resource_load(const char *filename, void *(*load)(size_t size, void *data), void (*release)(void *), void **ptr);
void resource_barrier(void);
void resource_deinit(void);

#endif
