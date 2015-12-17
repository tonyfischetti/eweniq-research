
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sll-recur-poly-sent-good.h"


/*********************************************************************
 *                                                                   *
 *   implementation of search structure for uneek via a              *
 *   polymorphic singly linked list                                  *
 *                                                                   *
 *********************************************************************/


item* insert(item* the_first, void* the_data){
    /*****************************************
     * `insert` inserts an item into the     *
     * list pointed to in the first          *
     * argument. the item inserted contains  *
     * the data from the pointed to by the   *
     * void pointer in the second argument.  *
     * it returns a pointer to the new head  *
     *****************************************/
    item* new_first = malloc(sizeof(item));
    new_first->data = the_data;
    new_first->next = the_first;
    return new_first;
}



item* find(item* an_item, item* tail, void* looking_for,
        int (*cmp_fn)(item*, void*)){
    if(!an_item){
        item* retval = NULL;
        return retval;
    }

    tail->data = looking_for;

    item* result;
    result = find_helper(an_item, looking_for, cmp_fn);

    /* tail->data = old_sentinel_data; */
    return result;
}



item* find_helper(item* an_item, void* looking_for, int (*cmp_fn)(item*, void*)){
    int result = (*cmp_fn)(an_item, looking_for);

    if(result==0){
        if(an_item->sentinel){
            item* retval = NULL;
            return retval;
        }
        return an_item;
    }
    return find_helper(an_item->next, looking_for, cmp_fn);
}




void display(item* an_item, void (*disp_fn)(item*)){
    /*********************************************
     * `display` takes a pointer to an item in a *
     * singly-linked list (usually the first     *
     * item) and a pointer to a void function    *
     * that takes an item and displays it.       *
     * `display` calls recursively displays all  *
     * elements by calling itself with the next  *
     * item                                      *
     *********************************************/
    (*disp_fn)(an_item);

    if(an_item->next){
        display(an_item->next, disp_fn);
    }
}
