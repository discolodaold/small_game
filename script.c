struct script {
    const char *start;
    const char *pos;
    const char *end;
};

static struct script *_current;

static void *_load(size_t size, char *data) {
    struct script *result = malloc(sizeof(*result));
    result->start = strdup(data);
    result->pos = result->start;
    result->end = result->start + strlen(result->start);
    return result;
}

static void _release(void *ptr) {
    free(*(void **)ptr);
    free(ptr);
}

void script_init(void) {
}

void script_set(const char *name) {
    _current = NULL;
    resource_load(name, &_load, &_release, &_current);
}

