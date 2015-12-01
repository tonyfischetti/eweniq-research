
#ifndef SIMPTREE_H
#define SIMPTREE_H

typedef struct _item item;

struct _item {
    void* data;
    item* left;
    item* right;
};

item* make_node(void*);

bool insert(item*, void*, int (*cmp_fn)(item*, void*));

void display(item*);

#endif

