#ifndef STACK_H
#define STACK_H

typedef struct stack{
    int* arr;
    int top;
    int maxsize;
    void* sem;
}stack;

// multiple threads could be accessing common stack.
// all of the functions declared below must be thread safe.

// create stack
stack* create_stack();

// insert into stack by value
void push(stack* st, int data);

// delete from stack by value
int pop(stack* st);

// delete stack
void delete_stack(stack* st);

#endif
