#ifndef SYS_H
#define SYS_H

#include "proc.h"

extern float current_time;

void sys_init(void);
void sys_sleep(unsigned int ms);

#endif
