#ifndef SLL_H
#define SLL_H

typedef struct _item item;

struct _item {
    void* data;
    item* next;
};

item* insert(item*, void*);


item* find(item*, item*, void*, int (*cmp_fn)(item*, void*));

item* find_helper(item*, void*, int (*cmp_fn)(item*, void*));

void display(item*, void (*disp_fn)(item*));

#endif

