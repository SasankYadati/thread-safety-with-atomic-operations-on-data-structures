#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include"stack.h"
#define MAXSIZE 1000
// create stack
stack* create_stack()
{
    /*
       create a stack
       associate with each stack a top
       and a semaphore to perform thread safe operations
    */
    stack* st = (stack*)malloc(sizeof(stack));
    st->arr = (int*)malloc(sizeof(int)*MAXSIZE);
    st->top = -1;
    st->maxsize = MAXSIZE;
    st->sem = (sem_t*)malloc(sizeof(sem_t));
    
    sem_init(st->sem,0,1);

    return st;
}

// insert into stack by value
void push(stack* st, int data)
{
    sem_t* sem = st->sem;
    sem_wait(sem);
    
    if(st->top==st->maxsize-1) // stack full
    {
        printf("Full stack. Push fail.\n");
        goto end_cs;
    }
    
    int ind = ++(st->top);
    st->arr[ind] = data;

    end_cs:
    sem_post(sem);
}

// delete from stack by value
int pop(stack* st)
{
    sem_t* sem = st->sem;
    sem_wait(sem);

    if(st->top==-1) // stack empty
    {
        printf("Empty stack. Pop fail.\n");
        goto end_cs;
    }

    int data = st->arr[(st->top)--];

    end_cs:
    sem_post(sem);
    return data;
}

// delete stack
void delete_stack(stack* st)
{
    sem_t* sem = st->sem;
    sem_wait(sem);

    free(st);
    st = NULL;

    sem_post(sem);
}
