

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sll-recur-poly.h"

/* If you set *line to null, and *length to zero, before the call,
 * then getline allocates the initial buffer for you by calling malloc */
char *line = NULL;
size_t length = 0u;
ssize_t n;



void print_item(item* an_item){
    printf("item: %s", (char *)(an_item->data));
}
void (*disp_fn)(item*) = &print_item;


int item_compare(item* first, void* second){
    char* f_d = (char*)(first->data);
    return strcmp(f_d, (char*)second);
}
int (*cmp_fn)(item*, void*) = &item_compare;


int main(void){

    item* my_list = NULL;
    item* tail = NULL;

    /* first */
    n = getline(&line, &length, stdin);
    printf("%s", line);
    fflush(stdout);
    char* the_string = malloc(n * sizeof(char) + 1);
    strcpy(the_string, line);
    my_list = insert(my_list, (void*)(the_string));
    tail = my_list;

    while((n = getline(&line, &length, stdin)) >= 0){
        char* the_string = malloc(n * sizeof(char) + 1);
        strcpy(the_string, line);

        if(!find(my_list, tail, (void*)(the_string), cmp_fn)){
            printf("%s", line);
            fflush(stdout);
            my_list = insert(my_list, (void*)(the_string));
        }
    }
    free(line);

    return 0;
}
