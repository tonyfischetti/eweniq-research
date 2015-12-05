
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


void shift(item** root_address, const char* direction,
        int (*cmp_fn)(item*, item*)){
    item* replacement;
    item* move = *root_address;
    printf("shifting: %s\n", (char*)move->data);
    if(strcmp(direction, "left")==0)
        replacement = move->right;
    else
        replacement = move->left;
    /* cant move */
    if(!replacement)
        return;
    item* parent = move->parent;
    replacement->parent = parent;
    if(strcmp(direction, "left")==0)
        move->right=NULL;
    else
        move->left=NULL;

    insert(replacement, move, cmp_fn);

    *root_address = replacement;
    if(!parent)
        return;

    int comp = cmp_fn(parent, replacement);
    if(comp > 0)
        parent->left = replacement;
    else
        parent->right = replacement;
        
    *root_address = replacement;
    return;
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

int balance(item** root_address, int (*cmp_fn)(item*, item*)){
    item* move = *root_address;
    printf("balanced called on %s\n", (char*)move->data);
    display(stdout, move);
    write_dot_file("try.txt", move);
    if(imbalanced_p(move)==0){
        printf("balanced!\n");
        printf("why dont you stop!\n");
        /* if(strcmp((char*)move->data, "12")==0){ */
        /*         write_dot_file("try.txt", move); */
        /*     exit(0); */
        /* } */
        return 1;
    }
    printf("it's imbalanced\n");
    if(imbalanced_p(*root_address)==-1){
        shift(root_address, "right", cmp_fn);
        balance(root_address, cmp_fn);
    }
    if(imbalanced_p(*root_address)==1){
        shift(root_address, "left", cmp_fn);
        balance(root_address, cmp_fn);
    }
    return 1;
}


int balance_children(item** root_address, int (*cmp_fn)(item*, item*)){
    printf("balance_children called\n");
    item* move = *root_address;
    if(!move)
        return 1;
    printf("called with\n");
    display(stdout, move);
    int im_c = imbalanced_p(move);
    printf("here\n");
    if(im_c != 0){
        printf("there\n");
        balance(&move, cmp_fn);
        printf("everywhere\n");
    }
    int im_l = imbalanced_p(move->left);
    int im_r = imbalanced_p(move->right);
    if(im_l == 0 && im_r == 0)
        return 1;
    return (balance_children(&(move->right), cmp_fn) +
            balance_children(&(move->left), cmp_fn));
    /* return (balance_children(&(move->left), cmp_fn) + */
    /*         balance_children(&(move->right), cmp_fn)); */
}

int balance_tree(item** root_address, int (*cmp_fn)(item*, item*)){
    balance(root_address, cmp_fn);
    printf("balanced once\n");
    balance_children(root_address, cmp_fn);
    return 1;
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

