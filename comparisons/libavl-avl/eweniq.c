

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "avl.h"

/* If you set *line to null, and *length to zero, before the call,
 * then getline allocates the initial buffer for you by calling malloc */
char *line = NULL;
size_t length = 0u;
ssize_t n;





int item_compare(const void* first, const void* second, void* param){
    char* f_d = (char*)(first);
    char* s_d = (char*)(second);
    return strcmp(f_d, s_d);
}
int (*cmp_fn)(const void*, const void*, void*) = &item_compare;


int main(void){

    struct avl_table* table = avl_create(cmp_fn, NULL, NULL);


    while((n = getline(&line, &length, stdin)) >= 0){
        char* the_string = malloc(n * sizeof(char) + 1);
        strcpy(the_string, line);
        the_string[n-1] = '\0';
        if(avl_insert(table, (void*)(the_string)) == NULL){
            printf("%s", line);
            fflush(stdout);
        }
    }
    free(line);

    /* balance_tree(&root, cmp_fn); */
    /* printf("done second\n"); */
    /* write_dot_file("balanced.txt", root); */


    return 0;
}
