

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
    }


    while((n = getline(&line, &length, stdin)) >= 0){
        char* the_string = malloc(n * sizeof(char) + 1);
        strcpy(the_string, line);
        the_string[n-1] = '\0';
        item* new_node = make_node((void*)(the_string));
        if(insert(root, new_node, cmp_fn)){
            printf("inserted %s whose parent is %s\n",
                    line, (char*)new_node->parent->data);
            printf("%s", line);
            fflush(stdout);
        }
    }
    free(line);

    write_dot_file("one.txt", root);
    root = shift_left(root, root->right, cmp_fn);
    printf("is it an error in display?\n");
    write_dot_file("two.txt", root);
    printf("nope\n");
    /* root = shift_left(root, root, cmp_fn); */
    /* write_dot_file("three.txt", root); */
    /* root = shift_left(root, root, cmp_fn); */
    /* write_dot_file("four.txt", root); */
    /* root = shift_right(root, root, cmp_fn); */
    /* write_dot_file("five.txt", root); */


    printf("total: %d\n", count_nodes(root));
    printf("left: %d\n", count_nodes(root->left));
    printf("right: %d\n", count_nodes(root->right));

    return 0;
}
