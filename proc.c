#include "proc.h"

#include <stdlib.h>
#include <string.h>

struct proc_message {
    struct proc_message *next;
    char *type;
    void *data;
};

struct proc_message *_free_messages;

static struct proc_message *_allocate_message(void) {
    struct proc_message *m;
    if(_free_messages) {
        m = _free_messages;
        _free_messages = m->next;
    } else {
        m = malloc(sizeof(*m));
    }
    return m;
}

struct proc {
    struct proc *next;
    unsigned int lc;
    unsigned int (*func)(unsigned int *, void *, float *);
    void *data;
    float sleep;
    struct proc_message *messages;
};

static struct proc *_free_procs;
static struct {
    struct proc *first;
    struct proc *current;
    struct proc *last;
} _active;

void proc_init(void) {
    _free_messages = NULL;
    _free_procs = NULL;
    _active.first = NULL;
    _active.current = NULL;
    _active.last = NULL;
}

struct proc *proc_spawn(unsigned int (*func)(unsigned int *, void *, float *), void *data) {
    struct proc *p;
    if(_free_procs) {
        p = _free_procs;
        _free_procs = p->next;
    } else {
        p = calloc(1, sizeof(*p));
    }
    p->next = NULL;
    p->lc = 0;
    p->func = func;
    p->data = data;

    if(_active.first == NULL) {
        _active.first = p;
    }
    if(_active.last) {
        _active.last->next = p;
    }
    _active.last = p;

    return p;
}

void proc_send(struct proc *proc, char *type, void *data) {
    struct proc_message *m = _allocate_message();
    m->next = proc->messages;
    m->type = strdup(type);
    m->data = data;
    proc->messages = m;
}

void *proc_receive(char *type) {
    struct proc_message *m = _active.current->messages, *last_m = NULL;
    while(m) {
        if(strcmp(type, m->type) == 0) {
            if(last_m) {
                last_m->next = m->next;
            } else {
                _active.current->messages = m->next;
            }
            free(m->type);
            m->next = _free_messages;
            _free_messages = m;
            return m->data;
        }
        m = m->next;
    }
    return NULL;
}

static void _dump_messages(struct proc *p) {
    struct proc_message *m = p->messages, *next;
    while(m) {
        next = m->next;
        free(m->type);
        m->next = _free_messages;
        _free_messages = m;
        m = next;
    }
    p->messages = NULL;
}

void proc_dump_messages(void) {
    _dump_messages(_active.current);
}

struct proc *proc_current(void) {
    return _active.current;
}

static int _running;
void proc_start_loop(void) {
    _running = 1;
    while(_running) {
        struct proc *last_current = NULL;
        _active.current = _active.first;
        while(_running && _active.current) {
            switch(_active.current->func(&_active.current->lc, _active.current->data, &_active.current->sleep)) {
            case PROC_WAIT:
            case PROC_YIELD:
                last_current = _active.current;
                break;
            case PROC_EXIT:
            case PROC_END:
                proc_dump_messages();
                if(last_current) {
                    last_current->next = _active.current->next;
                } else {
                    _active.first = _active.current->next;
                }
                if(last_current->next == NULL) {
                    _active.last = last_current;
                }
                _active.current->next = _free_procs;
                _free_procs = _active.current;
                break;
            }
            _active.current = _active.current->next;
        }
    }
}

void proc_end_loop(void) {
    _running = 0;
}

void proc_deinit(void) {
    struct proc *p = _active.first, *p_next;
    struct proc_message *m, *m_next;
    _running = 0;
    while(p) {
        p_next = p->next;
        _dump_messages(p);
        p->next = _free_procs;
        _free_procs = p;
        p = p_next;
    }
    p = _free_procs;
    while(p) {
        p_next = p->next;
        free(p);
        p = p_next;
    }
    m = _free_messages;
    while(m) {
        m_next = m->next;
        free(m);
        m = m_next;
    }
}

