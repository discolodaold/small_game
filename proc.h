#ifndef PROC_H
#define PROC_H

struct proc;

struct proc *proc_spawn(unsigned int (*func)(unsigned int *, void *, float *), void *data);
void proc_send(struct proc *proc, char *type, void *data);
void *proc_receive(char *type);
void proc_dump_messages(void);
struct proc *proc_current(void);
void proc_init(void);
int proc_frame(void);
void proc_end_all(void);
void proc_deinit(void);

#define LC_INIT(s) s = 0;
#define LC_RESUME(s) switch(s) { case 0:
#define LC_SET(s) s = __LINE__; case __LINE__:
#define LC_END(s) }

enum {
    PROC_WAIT,
    PROC_YIELD,
    PROC_EXIT,
    PROC_END
};

#define proc(NAME) unsigned int NAME(unsigned int *__lc__, void *data, float *__sleep__)
#define proc_begin() { int __yield__ = 1; LC_RESUME(*__lc__)
#define proc_wait(COND) \
    do { \
        LC_SET(*__lc__); \
        if(!(COND)) { \
            return PROC_WAIT; \
        } \
    } while(0)
#define proc_yield() \
    do { \
        __yield__ = 0; \
        LC_SET(*__lc__); \
        if(__yield__ == 0) { \
            return PROC_YIELD; \
        } \
    } while(0)
#define proc_sleep(TIME) \
    do { \
        *__sleep__ = nos_time() + time; \
        LC_SET(*__lc__); \
        if(*__sleep__ < nos_time()) { \
            return PROC_YIELD; \
        } \
    } while(0)
#define proc_exit() \
    do { \
        *__lc__ = 0; \
        return PROC_EXIT; \
    } while(0)
#define proc_end() LC_END(*__lc__); __yield__ = 0; return PROC_END; }

#endif
