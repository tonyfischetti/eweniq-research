
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

    if(result == 0)
        return false;

    if(result > 0){
        if(!root->left){
            root->left = new_node;
            root->left->parent = root;
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


item* shift(item* root, item* move, const char* direction,
        int (*cmp_fn)(item*, item*)){
    item* replacement;
    if(strcmp(direction, "left")==0)
        replacement = move->right;
    else
        replacement = move->left;
    /* cant move */
    if(!replacement)
        return root;
    item* parent = move->parent;
    replacement->parent = parent;
    if(strcmp(direction, "left")==0)
        move->right=NULL;
    else
        move->left=NULL;

    insert(replacement, move, cmp_fn);

    if(!replacement->parent){
        printf("there?\n");
        return replacement;
    }

    int comp = cmp_fn(parent, replacement);

    if(comp > 0)
        parent->left = replacement;
    else
        parent->right = replacement;
        
    return replacement;
    return root;
}


int imbalanced_p(item* root){
    if(!root)
        return 0;
    int left  = count_nodes(root->left);
    int right = count_nodes(root->right);
    if(left > (right+1))
        return -1;
    if(right > (left+1))
        return 1;
    return 0;
}

item* balance(item* root, item* move, int (*cmp_fn)(item*, item*)){
    printf("move is now:\n");
    display(stdout, move);
    printf("is it imbalanced?: %d\n", imbalanced_p(move));
    if(imbalanced_p(move)==0){
        printf("returning\n");
        return move;
    }
    if(imbalanced_p(move)==-1){
        item* root = NULL;
        printf("shifting right\n");
        move = shift(root, move, "right", cmp_fn);
        printf("made it here\n");
        return balance(root, move, cmp_fn);
    }
    if(imbalanced_p(move)==1){
        item* root = NULL;
        printf("shifting left\n");
        move = shift(root, move, "left", cmp_fn);
        printf("in move is now:\n");
        display(stdout, move);
        fflush(stdout);
        return balance(root, move, cmp_fn);
    }
    return NULL;
}

void balance_children(item* root, item* move, int (*cmp_fn)(item*, item*)){
    printf("balance children called\n");
    if(!move)
        return;
    printf("move is \n");
    display(stdout, move);
    int im_l = imbalanced_p(move->left);
    printf("maybe\n");
    int im_r = imbalanced_p(move->right);
    printf("left and right are %d and %d\n", im_l, im_r);
    if(im_l == 0 && im_r == 0)
        return;
    if(im_l !=0){
        move = balance(root, move->left, cmp_fn);
        return balance_children(root, move->left, cmp_fn);
    }
    if(im_r != 0){
        move = balance(root, move->right, cmp_fn);
        return balance_children(root, move->right, cmp_fn);
    }
    return;
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

