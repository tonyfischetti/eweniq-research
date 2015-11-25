#ifndef SLL_H
#define SLL_H

typedef struct _item item;

struct _item {
    char* data;
    item* next;
};

item* insert(item*, char*);

item* find(item*, char*);

void display(item*, void (*disp_fn)(item*));

#endif

