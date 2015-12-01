

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "simple-bin-tree.h"

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

    item* root = NULL;


    if((n = getline(&line, &length, stdin)) >= 0){
        char* the_string = malloc(n * sizeof(char) + 1);
        strcpy(the_string, line);
        the_string[n-1] = '\0';
        root = make_node((void*)the_string);
    }


    while((n = getline(&line, &length, stdin)) >= 0){
        char* the_string = malloc(n * sizeof(char) + 1);
        strcpy(the_string, line);
        the_string[n-1] = '\0';

        if(insert(root, (void*)(the_string), cmp_fn)){
            printf("%s", line);
            fflush(stdout);
        }
    }
    free(line);

    display(root);

    return 0;
}
