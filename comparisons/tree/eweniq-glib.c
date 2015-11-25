

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

/* If you set *line to null, and *length to zero, before the call,
 * then getline allocates the initial buffer for you by calling malloc */
char *line = NULL;
size_t length = 0u;
ssize_t n;


gint item_compare(gconstpointer first, gconstpointer second){
    return strcmp((char*)first, (char*)second);
}
gint (*cmp_fn)(gconstpointer, gconstpointer) = &item_compare;


int main(void){

    GTree* my_tree = g_tree_new(cmp_fn);
    char value = 'a';

    while((n = getline(&line, &length, stdin)) >= 0){
        char* the_string = malloc(n * sizeof(char) + 1);
        strcpy(the_string, line);

        if(!g_tree_lookup(my_tree, the_string)){
            printf("%s", line);
            fflush(stdout);
            g_tree_insert(my_tree, the_string, &value);
        }
    }
    free(line);

    return 0;
}
