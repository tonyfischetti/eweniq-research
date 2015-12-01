
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "simple-bin-tree.h"


/*********************************************************************
 *                                                                   *
 *   implementation of search structure for uneek via a              *
 *   simple binary search tree                                       *
 *                                                                   *
 *********************************************************************/



item* make_node(void* the_data){
    item* new_node  = malloc(sizeof(item));
    new_node->data  = the_data;
    new_node->left  = NULL;
    new_node->right = NULL;
    return new_node;
}



bool insert(item* root, void* the_data, int (*cmp_fn)(item*, void*)){
    if(!root->data){
        root->data = make_node(the_data);
        return true;
    }

    int result = (*cmp_fn)(root, the_data);

    if(result == 0)
        return false;

    if(result < 0){
        if(!root->left){
            root->left = make_node(the_data);
            return true;
        }
        return insert(root->left, the_data, cmp_fn);
    }

    /* greater than 1 */
    if(!root->right){
        root->right = make_node(the_data);
        return true;
    }

    return insert(root->right, the_data, cmp_fn);
}



void display(item* root){

    if(!root)
        return;

    if(root->left){
        printf("\"%s\" -> \"%s\";\n", (char*)root->data, 
                (char*)root->left->data);
        display(root->left);
    }

    if(root->right){
        printf("\"%s\" -> \"%s\";\n", (char*)root->data,
                (char*)root->right->data);
        display(root->right);
    }

} 


