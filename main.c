#include "proc.h"
#include "animation.h"
#include "sys.h"
#include "resource.h"

#include <stdlib.h>
#include <stdio.h>

float current_time;
int line_count;

proc(fps) {
    proc_begin();
    while(1) {
        sys_sleep(16);
        proc_yield();
    }
    proc_end();
    proc_spawn(fps, NULL);
}

void game_init(void) {
    proc_init();
    sys_init();
    resource_init();
    proc_spawn(fps, NULL);
}

void game_deinit(void) {
    resource_deinit();
    proc_deinit();
    exit(0);
}

proc(lines) {
    int i;
    proc_begin();
    while(1) {
        char spaces[] = "                                                                                                    "
                        "                                                                                                    ";
        if(proc_receive("animation end")) {
            proc_end_loop();
            proc_yield();
        }
        printf("\r%.*s*%.*s", line_count, spaces, 99-line_count, spaces);
        fflush(stdout);
        proc_yield();
    }
    proc_end();
}

static int _test_int, *_test_data;

static void *_test_load(size_t length, void *buffer) {
    printf("%s\n", (char *)buffer);
    return &_test_int;
}

static void _test_release(void *data) {
    printf("released\n");
}

int main(int argc, char *argv[]) {
    game_init();

    resource_load("main.c", _test_load, _test_release, (void **)&_test_data);
    resource_load("main.c", _test_load, _test_release, (void **)&_test_data);

    animate_int(proc_spawn(lines, NULL), &line_count, 0, 100, 2.0, easeOutBounce);

    proc_start_loop();

    game_deinit();
}

