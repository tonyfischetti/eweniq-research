
#ifndef SIMPTREE_H
#define SIMPTREE_H

typedef struct _item item;

struct _item {
    void* data;
    item* left;
    item* right;
    item* parent;
};

item* make_node(void*);

bool insert(item*, item*, int (*cmp_fn)(item*, item*));

int count_nodes(item*);

item* shift(item*, item*, const char*, int (*cmp_fn)(item*, item*));

int imbalanced_p(item* root);

item* balance(item*, item*, int (*cmp_fn)(item*, item*));

void display(FILE*, item*);

void write_dot_file(const char*, item*);

#endif

