
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
    new_node->parent = NULL;
    return new_node;
}



bool insert(item* root, item* new_node, int (*cmp_fn)(item*, item*)){
    if(!root->data){
        root->data = new_node;
        return true;
    }

    int result = (*cmp_fn)(root, new_node);
    printf("result %i\n", result);

    if(result == 0)
        return false;

    if(result > 0){
        if(!root->left){
            root->left = new_node;
            root->left->parent = root;
            printf("here\n");
            return true;
        }
        return insert(root->left, new_node, cmp_fn);
    }

    /* less than 1 */
    if(!root->right){
        root->right = new_node;
        root->right->parent = root;
        return true;
    }

    return insert(root->right, new_node, cmp_fn);
}



int count_nodes(item* root){
    if(!root)
        return 0;
    if(!root->left && !root->right)
        return 1;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}


item* shift_left(item* root, item* move, int (*cmp_fn)(item*, item*)){

    item* replacement = move->right;
    /* cant move right */
    if(!replacement)
        return root;
    item* parent = move->parent;
    printf("parent is: %s\n", (char*)parent->data);
    replacement->parent = parent;
    move->right=NULL;

    printf("moving this\n");
    display(stdout, move);
    printf("\n");
    printf("to this\n");
    display(stdout, replacement);
    printf("\n");
    insert(replacement, move, cmp_fn);

    printf("makes: \n");
    display(stdout, replacement);

    int comp = cmp_fn(root, move);

    printf("there\n");
    if(comp==0)
        return replacement;

    printf("everywhere\n");
    printf("parent is: %s\n", (char*)parent->data);
    comp = cmp_fn(parent, replacement);

    if(comp > 0)
        parent->left = replacement;
    else
        parent->right = replacement;
        

    return root;
}



void display(FILE* file, item* root){

    if(!root)
        return;

    if(root->left){
        fprintf(file,
                "\"%s\" -> \"%s\" [label=\"left\"];\n", (char*)root->data,
                (char*)root->left->data);
        display(file, root->left);
    }

    if(root->right){
        fprintf(file,
                "\"%s\" -> \"%s\" [label=\"right\"];\n", (char*)root->data, 
                (char*)root->right->data);
        display(file, root->right);
    }

} 


void write_dot_file(const char* filename, item* root){
    FILE* file = fopen(filename, "w");
    fprintf(file, "strict digraph TheTree {\n");
    display(file, root);
    fprintf(file, "}\n");
    fclose(file);
    return;
}
