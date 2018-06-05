#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct linked_list_node{
    int data;
    struct linked_list_node* next;
}linked_list_node;

typedef struct linked_list{
    struct linked_list_node* head;
    void* sem;
}linked_list;

// multiple threads could be accessing common linked_list.
// all of the functions declared below must be thread safe.

// create linked_list
linked_list* create_ll();

// insert into linked_list by value
void insert_in_ll(linked_list* list, int data);

// delete from linked_list by value
void delete_from_ll(linked_list* list, int data);

// search in linked_list by value
int search_ll(linked_list* list, int data);

// length of linked_list
int length_ll(linked_list* list);

// delete linked_list
void delete_ll(linked_list* list);

#endif
