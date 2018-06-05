#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include"linked_list.h"

// create linked_list
linked_list* create_ll()
{
        // associate with each linked_list a semaphore.
        // only one thread can operate on a given linked_list at any point of time.
        // therefore, one semaphore for each linked_list.

        linked_list* list = (linked_list*)malloc(sizeof(linked_list));
        list->head = NULL;
        list->sem = (sem_t*)malloc(sizeof(sem_t));
        sem_init(list->sem, 0, 1);
        return list;
}


// insert into linked_list by value
void insert_in_ll(linked_list* list, int data)
{
    /*

    */
    sem_t* sem = list->sem;
    sem_wait(sem);
    // enter critical section
    linked_list_node* head = list->head;
    if(head==NULL) // empty linked_list
    {
        list->head = (linked_list_node*)malloc(sizeof(linked_list_node));
        list->head->data = data;
        list->head->next = NULL;
    }
    else // non empty linked_list
    {
        // find last linked_list_node
        while(head->next!=NULL)
        {
            head = head->next;
        }
        head->next = (linked_list_node*)malloc(sizeof(linked_list_node));
        head = head->next;
        head->data = data;
        head->next = NULL;
    }
    // exit critical section
    sem_post(sem);
}

// delete from linked_list by value
void delete_from_ll(linked_list* list, int data)
{
    /*
    delete the first occurence of data in the linked_list
    */
    sem_t* sem = list->sem;
    sem_wait(sem);
    // enter critical section
    linked_list_node* head = list->head;
    linked_list_node* prev = NULL;

    if(head==NULL) // empty linked_list
        goto end_cs; // instead of returning goto the last statement in the critical section
    else // non empty linked_list
    {
        while(head!=NULL && head->data!=data)
        {
            prev = head;
            head = head->next;
        }

        if(head==NULL) // not found
            goto end_cs; // instead of returning goto the last statement in the critical section
        else // found the element
        {
            if(prev==NULL) // first element
            {
                list->head = list->head->next; // move the head
                free(head); // free the node to be deleted
            }
            else // not first element
            {
                prev->next = head->next; // change prev's link
                free(head); // free the node to be deleted
            }
        }
    }

    end_cs: // a label at the end of critical section
    // exit critical section
    sem_post(sem);
}

// search in linked_list by value
int search_ll(linked_list* list, int data)
{
    /*
    search for the first occurence of data in linked_list
    return the index of data
    */
    sem_t* sem = list->sem;
    sem_wait(sem);
    // enter critical section
    linked_list_node* head = list->head;
    int index;
    if(head==NULL) // empty linked_list
    {
        index = -1;
        goto end_cs; // go to the end of critical section
    }
    else // non-empty linked_list
    {
        index = 0;
        while(head!=NULL && head->data!=data)
        {
            index++;
            head = head->next;
        }
        if(head==NULL) // not found
        {
            index = -1;
            goto end_cs;
        }
        else // found the element
        {
            goto end_cs;
        }
    }

    end_cs: // a label at the end of critical section
    // exit critical section
    sem_post(sem);
    return index;
}

// length of linked_list
int length_ll(linked_list* list)
{
    /*
    returns the length of the linked_list
    */
    sem_t* sem = list->sem;
    sem_wait(sem);
    // enter critical section
    linked_list_node* head = list->head;
    int len=0;
    if(head==NULL)
    {
        goto end_cs;
    }
    else
    {
        while(head!=NULL)
        {
            len++;
            head = head->next;
        }
    }
    end_cs: // a label at the end of critical section
    // exit critical section
    sem_post(sem);
    return len;
}

// delete linked_list
void delete_ll(linked_list* list)
{
    /*
    only deletes nodes in the linked_list
    user has to free the list himself using free(list);
    */
    sem_t* sem = list->sem;
    sem_wait(sem);
    // enter critical section
    free(list);
    list = NULL;
    // exit critical section
    sem_post(sem);
}
