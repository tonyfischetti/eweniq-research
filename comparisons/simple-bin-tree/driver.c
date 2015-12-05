

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


int item_compare(item* first, item* second){
    char* f_d = (char*)(first->data);
    char* s_d = (char*)(second->data);
    return strcmp(f_d, s_d);
}
int (*cmp_fn)(item*, item*) = &item_compare;


int main(void){

    item* root = NULL;


    if((n = getline(&line, &length, stdin)) >= 0){
        char* the_string = malloc(n * sizeof(char) + 1);
        strcpy(the_string, line);
        the_string[n-1] = '\0';
        root = make_node((void*)the_string);
        printf("%s", line);
    }


    while((n = getline(&line, &length, stdin)) >= 0){
        char* the_string = malloc(n * sizeof(char) + 1);
        strcpy(the_string, line);
        the_string[n-1] = '\0';
        item* new_node = make_node((void*)(the_string));
        if(insert(root, new_node, cmp_fn)){
            printf("%s", line);
            fflush(stdout);
        }
    }
    free(line);

    write_dot_file("one.txt", root);
    balance(&root, cmp_fn);
    printf("done first\n");
    /* balance_children(&root, cmp_fn); */
    /* balance(&(root->left), cmp_fn); */
    item** something = &(root->left);
    balance(something, cmp_fn);
    /* #<{(| balance(&(root->right), cmp_fn); |)}># */
    /* #<{(| balance_tree(&root, cmp_fn); |)}># */
    printf("done second\n");
    write_dot_file("two.txt", root);
    /* shift(something, "right", cmp_fn); */
    /* display(stdout, *something); */
    /* shift(something, "right", cmp_fn); */
    /* display(stdout, *something); */
    /* shift(something, "right", cmp_fn); */
    /* display(stdout, *something); */
    /* shift(something, "right", cmp_fn); */
    /* display(stdout, *something); */
    /* shift(something, "right", cmp_fn); */
    /* display(stdout, *something); */
    /* shift(something, "right", cmp_fn); */
    /* display(stdout, *something); */


    return 0;
}
