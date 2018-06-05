#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue{
    int* arr;
    int rear;
    int maxsize;
    void* sem;
}queue;

// multiple threads could be accessing common queue.
// all of the functions declared below are thread safe.

// create queue
queue* create_queue();

// insert into queue
void enqueue(queue* q, int data);

// delete from queue
int dequeue(queue* q);

// delete queue
void delete_queue(queue* q);

#endif