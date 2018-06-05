#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

typedef struct binary_search_tree_node{
    int data;
    struct binary_search_tree_node* left;
    struct binary_search_tree_node* right;
}binary_search_tree_node;

typedef struct binary_search_tree{
    struct binary_search_tree_node* root;
    void* sem;
}binary_search_tree;

// multiple threads could be accessing common binary_search_tree.
// all of the functions declared below must be thread safe.
// 1. create
// 2. insert
// 3. search
// 4. delete
// 5. display


binary_search_tree* create_bst();

void insert_in_bst(binary_search_tree* bst, int data);

int search_bst(binary_search_tree* bst, int data);

void delete_from_bst(binary_search_tree* bst, int data);

void delete_bst(binary_search_tree* bst);


#endif
