#include "bst.h"
#include <stdlib.h>

struct node {
   int data; 
	
   struct node *leftChild;
   struct node *rightChild;
};

struct bst{
    size_t key_count;
    struct node *root;
};

bst_t *bst_create(void){
    bst_t *bst = malloc(sizeof *bst);

    if(bst == NULL){
        return NULL;
    }

    bst->key_count = 0;
    bst->root = NULL; 
    return bst; 
}

int bst_insert(bst_t *t, int key){
    if(t == NULL){                                          //NULL check
        return -1;
    }
    struct node *new_node = malloc(sizeof *new_node);       //declare new node using malloc
    if(new_node == NULL){                                   //NULL check 
        return -1;
    }
    
    new_node->data = key;                                 
    new_node->leftChild = NULL;
    new_node->rightChild = NULL;
    struct node *current = t->root;
    struct node *parent = NULL;

    if(t->root == NULL){
        t->root = new_node; 
        t->key_count++;
        return 0;
    }
    else{
        while(current != NULL){
            parent = current; 
            if(key < current->data){
                current = current->leftChild;
            }else{
                current = current->rightChild;
            }
        }
    }
    if(key < parent->data){
        parent->leftChild = new_node;
    }else{
        parent->rightChild= new_node;
    }
    t->key_count++; 
    return 0;
}

size_t bst_size(const bst_t *t){
    if(t == NULL){
        return 0;
    }
    else{
        return t->key_count;
    }
}

static size_t node_height(const struct node *node){
    if(node == NULL){
        return 0;
    }
    size_t leftHeight = node_height(node->leftChild);
    size_t rightHeight = node_height(node->rightChild);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

size_t bst_height(const bst_t *t){
    if(t == NULL){
        return 0;
    }
    else{
        return node_height(t->root);
    }
}

bool bst_contains(const bst_t *t, int key, size_t *visits){
    if(t == NULL){
        if(visits != NULL){
            *visits = 0;
        }
        return false;
    }
    struct node *current = t->root;
    size_t counter = 0;

    while(current != NULL && current->data != key){
        if(current->data > key){
            current = current->leftChild;
        }
        else{
            current = current->rightChild;
        }
        counter++;

        if(current == NULL){
            if(visits != NULL){
                *visits = counter;
            }
            return false;
        }
    }
    if(current == NULL){
        if(visits != NULL){
            *visits = counter;
        }
        return false;
    }
    counter++;
    if(visits != NULL){
        *visits = counter;
    }
    return true;
}

static void node_destroy(struct node *node){
    if(node == NULL){
        return;
    }
    node_destroy(node->leftChild);
    node_destroy(node->rightChild);
    free(node);
}

void bst_destroy(bst_t *t){
    if(t == NULL){
        return;
    }
    node_destroy(t->root);
    free(t);
}
