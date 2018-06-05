#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include "linked_list.h"
#include "binary_search_tree.h"
#include "stack.h"
#include "queue.h"

void *linklist1(void *ll);
void *linklist2(void *ll);
void *linklist3(void *ll);

void *bst1(void *bst);
void *bst2(void *bst);
void *bst3(void *bst);

void *stack1(void *st);
void *stack2(void *st);
void *stack3(void *st);

void *queue1(void *q);
void *queue2(void *q);
void *queue3(void *q);

int main()
{
    pthread_t pid1,pid2,pid3;

    // test linked list
    linked_list *llist = create_ll();
    pthread_create(&pid1,NULL,linklist1,(void*)llist);
    pthread_create(&pid2,NULL,linklist2,(void*)llist);
    pthread_create(&pid3,NULL,linklist3,(void*)llist);
    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);
    pthread_join(pid3,NULL);
    delete_ll(llist);
    printf("Thread tests on linked list : done\n");

    // test binary search tree
    binary_search_tree *tree = create_bst();
    pthread_create(&pid1,NULL,bst1,(void*)tree);
    pthread_create(&pid2,NULL,bst2,(void*)tree);
    pthread_create(&pid3,NULL,bst3,(void*)tree);
    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);
    pthread_join(pid3,NULL);
    delete_bst(tree);
    printf("Thread tests on binary search tree : done\n");

    // test stack
    stack *st = create_stack();
    pthread_create(&pid1,NULL,stack1,(void*)st);
    pthread_create(&pid2,NULL,stack2,(void*)st);
    pthread_create(&pid3,NULL,stack3,(void*)st);
    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);
    pthread_join(pid3,NULL);
    delete_stack(st);
    printf("Thread tests on stack : done\n");

    // test queue
    queue *q = create_queue();
    pthread_create(&pid1,NULL,queue1,(void*)q);
    pthread_create(&pid2,NULL,queue2,(void*)q);
    pthread_create(&pid3,NULL,queue3,(void*)q);
    pthread_join(pid1,NULL);
    pthread_join(pid2,NULL);
    pthread_join(pid3,NULL);
    delete_queue(q);
    printf("Thread tests on queue : done\n");
    
    return 0;
}

void *linklist1(void *ll)
{
    linked_list *head = (linked_list*)ll;
    insert_in_ll(head,5);
    sleep(1);
    insert_in_ll(head,15);
    sleep(1);
    delete_from_ll(head,15);
    sleep(1);
    insert_in_ll(head,25);
    sleep(1);
}
void *linklist2(void *ll)
{
    linked_list *head = (linked_list*)ll;
    insert_in_ll(head,10);
    sleep(1);
    insert_in_ll(head,20);
    sleep(1);
    delete_from_ll(head,20);
    sleep(1);
    insert_in_ll(head,30);
    sleep(1);
}
void *linklist3(void *ll)
{
    linked_list *head = (linked_list*)ll;
    insert_in_ll(head,12);
    sleep(1);
    insert_in_ll(head,22);
    sleep(1);
    delete_from_ll(head,22);
    sleep(1);
    insert_in_ll(head,32);
    sleep(1);
}

void *bst1(void *bst)
{
    binary_search_tree *BST = (binary_search_tree*)bst;
    insert_in_bst(BST,4);
    sleep(1);
    insert_in_bst(BST,10);
    sleep(1);
    delete_from_bst(BST,10);
    sleep(1);
    insert_in_bst(BST,2);
    sleep(1);
}
void *bst2(void *bst)
{
    binary_search_tree *BST = (binary_search_tree*)bst;
    insert_in_bst(BST,6);
    sleep(1);
    insert_in_bst(BST,12);
    sleep(1);
    delete_from_bst(BST,6);
    sleep(1);
    insert_in_bst(BST,8);
    sleep(1);
}
void *bst3(void *bst)
{
    binary_search_tree *BST = (binary_search_tree*)bst;
    insert_in_bst(BST,5);
    sleep(1);
    insert_in_bst(BST,15);
    sleep(1);
    delete_from_bst(BST,15);
    sleep(1);
    insert_in_bst(BST,8);
    sleep(1);
}

void *stack1(void *st)
{
    stack *ST = (stack*)st;
    push(ST,5);
    sleep(1);
    push(ST,15);
    sleep(1);
    pop(ST);
    sleep(1);
    push(ST,25);
    sleep(1);
}
void *stack2(void *st)
{
    stack *ST = (stack*)st;
    push(ST,3);
    sleep(1);
    push(ST,13);
    sleep(1);
    pop(ST);
    sleep(1);
    pop(ST);
    sleep(1);
}
void *stack3(void *st)
{
    stack *ST = (stack*)st;
    push(ST,5);
    sleep(1);
    push(ST,10);
    sleep(1);
    pop(ST);
    sleep(1);
    push(ST,20);
    sleep(1);
    pop(ST);
    sleep(1);
}

void *queue1(void *q)
{
    queue* Q = (queue*)q;
    enqueue(Q,5);
    sleep(1);
    enqueue(Q,15);
    sleep(1);
    dequeue(Q);
    sleep(1);
    enqueue(Q,15);
    sleep(1);
    dequeue(Q);
    sleep(1);
}
void *queue2(void *q)
{
    queue* Q = (queue*)q;
    enqueue(Q,3);
    sleep(1);
    enqueue(Q,6);
    sleep(1);
    dequeue(Q);
    sleep(1);
    enqueue(Q,9);
    sleep(1);
    dequeue(Q);
    sleep(1);
}
void *queue3(void *q)
{
    queue* Q = (queue*)q;
    enqueue(Q,10);
    sleep(1);
    enqueue(Q,20);
    sleep(1);
    dequeue(Q);
    sleep(1);
    enqueue(Q,30);
    sleep(1);
    dequeue(Q);
    sleep(1);
}