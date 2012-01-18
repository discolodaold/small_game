#include "data.c"

#include <stdlib.h>
#include <stdio.h>

struct map_branch {
    float x1, y1, x2, y2;
    int child; // a negative number is a leaf
};

enum {
    NUM_DIMENSIONS = 2,
    M              = (int)(512/sizeof(struct map_branch)),
    METHODS        = 1
};

struct rect {
    double boundry[NUM_DIMENSIONS * 2];
};

double rect_volume(struct rect *r) {
    double volume = 1;
    int i;
    for(i = 0; i < NUM_DIMENSIONS; ++i) {
        volume *= r->boundry[NUM_DIMENSIONS + i] - r->boundry[i];
    }
    return volume;
}

#define MIN(a,b) a<b?a:b
#define MAX(a,b) a>b?a:b

void rect_combine(struct rect *a, struct rect *b, struct rect *out) {
    int i;
    for(i = 0; i < NUM_DIMENSIONS; ++i) {
        out->boundry[i] = MIN(a->boundry[i], b->boundry[i]);
        out->boundry[NUM_DIMENSIONS + i] = MAX(a->boundry[NUM_DIMENSIONS + i], b->boundry[NUM_DIMENSIONS + i]);
    }
}

int rect_overlap(struct rect *a, struct rect *b) {
    int i;
    for(i = 0; i < NUM_DIMENSIONS; ++i) {
        if(a->boundry[i] > b->boundry[NUM_DIMENSIONS + i] || b->boundry[i] > a->boundry[NUM_DIMENSIONS + i]) {
            return 0;
        }
    }
    return 1;
}

int rect_contained(struct rect *a, struct rect *b) {
    int i, result = 1;
    for(i = 0; i < NUM_DIMENSIONS; ++i) {
        result = result && a->boundry[i] >= b->boundry[i] && a->boundry[NUM_DIMENSIONS + i] <= b->boundry[NUM_DIMENSIONS + i];
    }
    return result;
}

struct node;

struct branch {
    struct rect rect;
    union {
        unsigned int value;
        struct node *child;
    };
};

struct node {
    int count;
    int level;
    int id;
    struct branch branch[M];
};

void cover(struct node *n, struct rect *out) {
    int i;
    for(i = 0; i < M; ++i) {
        if(n->branch[i].child == 0) {
            continue;
        }
        *out = n->branch[i].rect;
        break;
    }
    for(i = 0; i < M; ++i) {
        rect_combine(&n->branch[i].rect, out, out);
    }
}

struct partition_vars {
    int partition[M + 1];
    int total, min_fill;
    int taken[M + 1];
    int count[2];
    struct rect cover[2];
    double area[2];
};

struct branch branch_buffer[M + 1];
int branch_count;
struct rect cover_split;
double cover_split_area;
struct partition_vars partitions[METHODS];

void init_rect(struct rect *rect) {
    int i;
    for(i = 0; i < NUM_DIMENSIONS*2; ++i) {
        rect->boundry[i] = 0.0;
    }
}

void init_branch(struct branch *branch) {
    init_rect(&branch->rect);
    branch->child = 0;
}

void init_node(struct node *node) {
    int i;
    node->count = 0;
    node->level = -1;
    for(i = 0; i < M; ++i) {
        init_branch(&node->branch[i]);
    }
}

void get_branches(struct node *node, struct branch *branch) {
    int i;
    for(i = 0; i < M; ++i) {
        branch_buffer[i] = node->branch[i];
    }
    branch_buffer[M] = *branch;
    branch_count = M + 1;

    cover_split = branch_buffer[0].rect;
    for(i = 1; i < M + 1; ++i) {
        rect_combine(&branch_buffer[i].rect, &cover_split, &cover_split);
    }
    cover_split_area = rect_volume(&cover_split);

    init_node(node);
}

void null_rect(struct rect *rect) {
    init_rect(rect);
    rect->boundry[0] = 1;
    rect->boundry[NUM_DIMENSIONS] = -1;
}

void init_partition_vars(struct partition_vars *p, int max_rects, int min_fill) {
    int i;

    p->count[0] = p->count[1] = 0;
    null_rect(&p->cover[0]);
    null_rect(&p->cover[1]);
    p->total = max_rects;
    p->min_fill = min_fill;
    for(i = 0; i < max_rects; ++i) {
        p->taken[i] = 0;
        p->partition[i] = -1;
    }
}

void classify(struct partition_vars *p, int group, int index) {
    p->partition[index] = group;
    p->taken[index] = 1;

    if(p->count[group] == 0) {
        p->cover[group] = branch_buffer[index].rect;
    } else {
        rect_combine(&p->cover[group], &branch_buffer[index].rect, &p->cover[group]);
    }
    p->area[group] = rect_volume(&p->cover[group]);
    p->count[group]++;
}

void pick_seeds(struct partition_vars *p) {
    int i, j, seed0, seed1;
    double worst, waste, area[M + 1];
    struct rect one_rect;

    for(i = 0; i < p->total; ++i) {
        area[i] = rect_volume(&branch_buffer[i].rect);
    }

    worst = -cover_split_area - 1;
    for(i = 0; i < p->total - 1; ++i) {
        for(j = i + 1; j < p->total; ++j) {
            rect_combine(&branch_buffer[i].rect, &branch_buffer[j].rect, &one_rect);

            waste = rect_volume(&one_rect) - area[i] - area[j];
            if(waste > worst) {
                worst = waste;
                seed0 = i;
                seed1 = j;
            }
        }
    }
    classify(p, 0, seed0);
    classify(p, 1, seed1);
}

void method_0(struct partition_vars *p, int min_fill) {
    int i, group, chosen, better_group;
    double biggest_diff, growth[2], diff;
    struct rect *r, rect[2];

    init_partition_vars(p, branch_count, min_fill);
    pick_seeds(p);

    while(p->count[0] + p->count[1] < p->total
       && p->count[0] < p->total - p->min_fill
       && p->count[1] < p->total - p->min_fill) {
        biggest_diff = -1;
        for(i = 0; i < p->total; ++i) {
            if(p->taken[i]) {
                continue;
            }
            for(group = 0; group < 2; ++group) {
                rect_combine(r, &p->cover[group], &rect[group]);
                growth[group] = rect_volume(&rect[group]) - p->area[group];
            }
            diff = growth[1] - growth[0];
            if(diff >= 0) {
                group = 0;
            } else {
                group = 1;
                diff = -diff;
            }
            if(diff > biggest_diff) {
                biggest_diff = diff;
                chosen = i;
                better_group = group;
            } else if(diff == biggest_diff && p->count[group] < p->count[better_group]) {
                chosen = i;
                better_group = group;
            }
        }
        classify(p, better_group, chosen);
    }

    if(p->count[0] + p->count[1] < p->total) {
        group = p->count[0] >= p->total - p->min_fill;
        for(i = 0; i < p->total; ++i) {
            if(!p->taken[i]) {
                classify(p, group, i);
            }
        }
    }
}

int add_branch(struct node *node, struct branch *branch, struct node **new_node);
void load_nodes(struct node *node, struct node *q, struct partition_vars *p) {
    int i;
    struct node *nodes[2] = {node, q};

    for(i = 0; i < p->total; ++i) {
        add_branch(nodes[p->partition[i]], &branch_buffer[i], 0);
    }
}

void split_node(struct node *node, struct branch *branch, struct node **new_node) {
    struct partition_vars *p;
    int level = node->level;

    get_branches(node, branch);

    p = &partitions[0];
    method_0(p, M/4);

    *new_node = malloc(sizeof(**new_node));
    (*new_node)->level = node->level = level;
    load_nodes(node, *new_node, p);
}

int add_branch(struct node *node, struct branch *branch, struct node **new_node) {
    int i;
    if(node->count < M) {
        for(i = 0; i < M; ++i) {
            if(node->branch[i].child == NULL) {
                node->branch[i] = *branch;
                node->count++;
            }
        }
        return 0;
    }
    split_node(node, branch, new_node);
    return 1;
}

int pick_branch(struct rect *rect, struct node *node) {
    struct rect *rr, tmp_rect;
    int i, best;
    double increase, best_increase = -1, area, best_area;
    for(i = 0; i < M; ++i) {
        if(node->branch[i].child == NULL) {
            continue;
        }
        rr = &node->branch[i].rect;
        rect_combine(rect, rr, &tmp_rect);
        best = i;
        best_area = rect_volume(rr);
        best_increase = rect_volume(&tmp_rect) - best_area;
        break;
    }
    for(; i < M; ++i) {
        if(node->branch[i].child == NULL) {
            continue;
        }
        rr = &node->branch[i].rect;
        area = rect_volume(rr);
        rect_combine(rect, rr, &tmp_rect);
        increase = rect_volume(&tmp_rect) - area;
        if(increase < best_increase || (increase == best_increase && area < best_area)) {
            best = i;
            best_area = area;
            best_increase = increase;
        }
    }
    return best;
}

int insert(struct rect *r, unsigned int value, struct node *n, struct node **new_node) {
    int i;
    struct branch b;
    struct node *n2;

    if(n->level) {
        i = pick_branch(r, n);
        if(!insert(r, value, n->branch[i].child, &n2)) {
            // child did not split
            rect_combine(r, &n->branch[i].rect, &n->branch[i].rect);
            return 0;
        }
        cover(n->branch[i].child, &n->branch[i].rect);
        b.child = n2;
        cover(n2, &b.rect);
        return add_branch(n, &b, new_node);
    }
    b.rect = *r;
    b.value = value;
    return add_branch(n, &b, new_node);
}

int insert_data(struct rect *r, unsigned int value, struct node **root) {
    struct node *new_node;
    struct branch b;
    if(insert(r, value, *root, &new_node)) {
        struct node *new_root = malloc(sizeof(*new_root));
        new_root->level = (*root)->level + 1;
        cover(*root, &b.rect);
        b.child = *root;
        add_branch(new_root, &b, NULL);
        cover(new_node, &b.rect);
        b.child = new_node;
        add_branch(new_root, &b, NULL);
        *root = new_root;
        return 1;
    }
    return 0;
}

void assign_id(struct node *node) {
    static int id = 0;
    int i;
    node->id = id++;
    if(node->level == 0) {
        return;
    }
    for(i = 0; i < M; ++i) {
        if(node->branch[i].child != NULL) {
            assign_id(node->branch[i].child);
        }
    }
}

void node_print(struct node *node) {
    int i;

    printf("\t{");
    char *branch_format = "\t\t{%f, %f, %f, %f, %d},\n";
    if(node->level == 0) {
        branch_format = "\t\t{%f, %f, %f, %f, -%d},\n";
    }
    for(i = 0; i < M; ++i) {
        printf(branch_format,
                node->branch[i].rect.boundry[0],
                node->branch[i].rect.boundry[1],
                node->branch[i].rect.boundry[2],
                node->branch[i].rect.boundry[3],
                node->branch[i].value);
    }
    printf("},\n");

    if(node->level) {
        for(i = 0; i < M; ++i) {
            if(node->branch[i].child) {
                node_print(node->branch[i].child);
            }
        }
    }
}

int main(int argc, char argv[]) {
    int i;
    struct data *d = game_data;
    struct rect rect;
    struct node *root = NULL;

    while(d->name) {
        if(d->kind == DODAD) {
            double width = game_data[d->base].width;
            double height = game_data[d->base].height;
            double x = d->x;
            double y = d->y;
            double rotation = d->rotation;
            rect.boundry[0] = x-width/2;
            rect.boundry[1] = y-height/2;
            rect.boundry[2] = x+width/2;
            rect.boundry[3] = y+width/2;
            insert_data(&rect, i, &root);
        }
        ++d;
    }

    if(root != NULL) {
        assign_id(root);
        node_print(root);
    }
}

