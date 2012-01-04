#include "sys.h"

#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

float current_time;
static struct timeval t_start;

static proc(update_time) {
    static struct timeval t;
    proc_begin();
    while(1) {
        gettimeofday(&t, NULL);
        current_time = (float)(t.tv_sec - t_start.tv_sec) + (float)(t.tv_usec - t_start.tv_usec) * 0.000001;
        proc_yield();
    }
    proc_end();
}

void sys_init(void) {
    gettimeofday(&t_start, NULL);
    proc_spawn(update_time, NULL);
}

void sys_sleep(unsigned int ms) {
    nanosleep(&(struct timespec){.tv_sec=0, .tv_nsec=ms*1000000}, NULL);
}

