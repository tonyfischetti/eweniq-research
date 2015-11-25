

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sll-recur-nonpoly.h"

/* If you set *line to null, and *length to zero, before the call,
 * then getline allocates the initial buffer for you by calling malloc */
char *line = NULL;
size_t length = 0u;
ssize_t n;



void print_item(item* an_item){
    printf("item: %s", (char *)(an_item->data));
}
void (*disp_fn)(item*) = &print_item;




int main(void){

    item* my_list = NULL;

    while((n = getline(&line, &length, stdin)) >= 0){
        char* the_string = malloc(n * sizeof(char) + 1);
        strcpy(the_string, line);

        if(!find(my_list, the_string)){
            printf("%s", line);
            fflush(stdout);
            my_list = insert(my_list, the_string);
        }
    }
    free(line);

    return 0;
}
