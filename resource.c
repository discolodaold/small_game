#include "resource.h"
#include "nos.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <pthread.h>

//{{{ A Fix for the ABA problem
#define CAS __sync_bool_compare_and_swap

union casPtr {
    uint64_t bits;
    struct {
        void     *ptr;
        uint32_t tag;
    };
};

static int casPtr_update(union casPtr *casPtr, void *new_ptr) {
    int64_t old_bits = casPtr->bits;
    union casPtr new_casPtr;
    new_casPtr.ptr = new_ptr;
    new_casPtr.tag = casPtr->tag + 1;
    return CAS(&casPtr->bits, old_bits, new_casPtr.bits);
}
//}}}

//{{{ Messages
struct loaderMessage {
    enum {
        MSG_LOAD,
        MSG_BARRIER,
        MSG_EXIT
    } tag;
    char *filename;
    void *(*load)(size_t size, void *data);
    void (*release)(void *);
    void **ptr;
};

// _head belongs to consumers (single)
static uint32_t _head;

// _tail belongs to producers (multiple)
static uint32_t _tail;

enum {
    MESSAGE_COUNT = 32
};
struct loaderMessage _messages[MESSAGE_COUNT];

// multiple producers
static void _enqueue(struct loaderMessage *m) {
    uint32_t tail;
    do {
        tail = _tail;
    } while(!CAS(&_tail, tail, tail + 1));
    _messages[tail & (MESSAGE_COUNT - 1)] = *m;
}

// single consumer
static struct loaderMessage *_dequeue(void) {
    uint32_t head;
    do {
        if(_head == _tail) {
            return NULL;
        }
        head = _head;
    } while(!CAS(&_head, head, head + 1));
    return &_messages[head & (MESSAGE_COUNT - 1)];
}
//}}}

struct resource {
    struct resource *next;
    char *filename;
    void (*release)(void *);
    void *data;
    unsigned int sequence;
};

static void *_loader(void *unused) {
    FILE *f;
    char *buffer;
    size_t length;
    struct resource *r, *active_resources = NULL, *free_resources = NULL, *r_next;
    struct loaderMessage *m;
    unsigned int sequence = 0;

    while(1) {
delt_with:
        m = _dequeue();
        if(m == NULL) {
            nos_sleep(16);
            continue;
        }

        if(m->tag == MSG_EXIT) {
            r = active_resources;
            while(r) {
                r_next = r->next;
                r->release(r->data);
#ifdef DEBUG
                free(r->filename);
#endif
                r->next = free_resources;
                free_resources = r;
                r = r_next;
            }
#ifdef DEBUG
            r = free_resources;
            while(r) {
                r_next = r->next;
                free(r);
                r = r_next;
            }
#endif
            return NULL;
        }

        if(m->tag == MSG_BARRIER) {
            r = active_resources;
            active_resources = NULL;
            while(r) {
                r_next = r->next;
                if(r->sequence != sequence) {
                    r->release(r->data);
                    free(r->filename);
                    r->next = free_resources;
                    free_resources = r;
                } else {
                    r->next = active_resources;
                    active_resources = r;
                }
                r = r_next;
            }
            sequence++;
            continue;
        }

        r = active_resources;
        while(r) {
            if(strcmp(r->filename, m->filename) == 0) {
                r->sequence = sequence;
                *m->ptr = r->data;
                free(m->filename);
                goto delt_with;
            }
            r = r->next;
        }

        if(free_resources) {
            r = free_resources;
            free_resources = r->next;
        } else {
            r = calloc(1, sizeof(*r));
        }

        f = fopen(m->filename, "r");
        if(f == NULL) {
            continue;
        }
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length + 1);
        if(buffer == NULL) {
            fclose(f);
            continue;
        }
        fread(buffer, 1, length, f);
        fclose(f);
        buffer[length] = 0;

        r->data = m->load(length, buffer);
        free(buffer);

        if(r->data) {
            *m->ptr = r->data;
            r->filename = m->filename;
            r->release = m->release;
            r->sequence = sequence;

            r->next = active_resources;
            active_resources = r;
        }
    }
}

static pthread_t _resource_thread;

void resource_init(void) {
    int r;

    _head = _tail = 0;

    if((r = pthread_create(&_resource_thread, NULL, _loader, NULL))) {
        printf("loader failed to start, %i\n", r);
    }
}

void resource_load(const char *filename, void *(*load)(size_t size, void *data), void (*release)(void *), void **ptr) {
    struct loaderMessage m;
    memset(&m, 0, sizeof(m));
    m.tag = MSG_LOAD;
    m.filename = strdup(filename);
    m.load = load;
    m.release = release;
    m.ptr = ptr;
    _enqueue(&m);
}

void resource_barrier(void) {
    struct loaderMessage m;
    memset(&m, 0, sizeof(m));
    m.tag = MSG_BARRIER;
    _enqueue(&m);
}

void resource_deinit(void) {
    struct loaderMessage m;
    memset(&m, 0, sizeof(m));
    m.tag = MSG_EXIT;
    _enqueue(&m);
    pthread_join(_resource_thread, NULL);
}

