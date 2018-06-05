#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include"queue.h"
#define MAXSIZE 1000
// create queue
queue* create_queue()
{
    /*
        create a queue
        associate with queue a rear
        and a semaphore to perform thread safe operations
    */
    queue* q = (queue*)malloc(sizeof(queue));
    q->arr = (int*)malloc(sizeof(int)*MAXSIZE);
    q->rear = -1;
    q->maxsize = MAXSIZE;
    q->sem = (sem_t*)malloc(sizeof(sem_t));

    sem_init(q->sem,0,1);

    return q;
}

// insert into queue
void enqueue(queue* q, int data)
{
    sem_t* sem = q->sem;
    sem_wait(sem);

    if(q->rear==q->maxsize-1) // queue full
    {
        printf("Full queue. Enqueue fail.\n");
        goto end_cs;
    }
    int ind = ++(q->rear);
    q->arr[ind] = data;

    end_cs:
    sem_post(sem);
}

// delete from queue
int dequeue(queue* q)
{
    sem_t* sem = q->sem;
    sem_wait(sem);

    if(q->rear==-1) // queue empty
    {
        printf("Empty queue. Dequeue fail.\n");
        goto end_cs;
    }

    int data = q->arr[(q->rear)--];

    end_cs:
    sem_post(sem);
    return data;
}

// delete queue
void delete_queue(queue* q)
{
    sem_t* sem = q->sem;
    sem_wait(sem);

    free(q);
    q = NULL;
    
    sem_post(sem);
}