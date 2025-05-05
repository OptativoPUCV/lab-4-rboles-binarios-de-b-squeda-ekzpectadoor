#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap *map = (TreeMap *)malloc(sizeof(TreeMap));
    if (map == NULL)
    {
        return NULL;
    }
    map->current = NULL;
    map->root = NULL;
    map->lower_than = lower_than;
    return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if (tree == NULL) return;
    TreeNode * nodo = tree->root;
    TreeNode * padre = NULL;
    while(nodo != NULL)
    {
        padre = nodo;
        void * currentKey = nodo->pair->key;
        if(tree->lower_than(currentKey, key))
        {
            nodo = nodo->right;
        }
        else if(tree->lower_than(key,currentKey))
        {
            nodo = nodo->left;
        }
        else
        {
            return;
        }
         
    }
    TreeNode * nuevoNodo = createTreeNode(key, value);
    nuevoNodo->parent = padre;
    if(tree->lower_than(padre->pair->key, key))
    {
       padre->right = nuevoNodo;
    }
    else
    {
        padre->left = nuevoNodo;
    }
    tree->current = nuevoNodo;
        

}

TreeNode * minimum(TreeNode * x){
    if(x == NULL)
    {
        return NULL;
    }
    while (x->left != NULL)
    {
        x = x->left;
    }
    

    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    if (tree == NULL)
    {
        return;
    }
    if(node == NULL)
    {
        return;
    }
    TreeNode * padre = node->parent;
    if((node->left == NULL) && (node->right == NULL))
    {
        if(padre->left == node)
        {
            padre->left = NULL;
        }
        else
        {
            padre->right = NULL;
        }
        free(node);
        return;
    }
    else if((node->left == NULL) || (node->right == NULL))
    {
        TreeNode * hijo = NULL;
        if(node->right != NULL)
        {
            hijo = node->right;
        }
        else{
            hijo = node->left;
        }
        if(padre->right == hijo)
        {
            padre->right = hijo;
        }
        else{
            padre->left = hijo;
        }
        hijo->parent = padre;
        free(node);
        return;
    }
    TreeNode *sucesor = node->right;
    while (sucesor->left != NULL) 
    {
        sucesor = sucesor->left;
    }
    free(node->pair);
    node->pair = sucesor->pair; 
    TreeNode *sucesor_parent = sucesor->parent;
    if (sucesor_parent->left == sucesor) {
        sucesor_parent->left = sucesor->right;
    } 
    else{
        sucesor_parent->right = sucesor->right;
    }    
    if (sucesor->right != NULL) {
        sucesor->right->parent = sucesor_parent;
        }
    free(sucesor);
    if (tree->current == node) {
        tree->current = NULL;
    }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL)
    {
        return NULL;
    }
    TreeNode * nodo = tree->root;
    while(nodo != NULL)
    {
        void* current_key = nodo->pair->key;
        if(tree->lower_than(key,current_key))
        {
            nodo = nodo->left;
        }
        else if(tree->lower_than(current_key, key))
        {
            nodo = nodo->right;
        }
        else
        {
            tree->current = nodo;
            return nodo->pair;
        }
    }
    return NULL;
    
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
