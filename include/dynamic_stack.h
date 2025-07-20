#ifndef STACK

#define STACK
#include <stdbool.h>

typedef struct _stack {
    struct _node* top;
    int size;
    int capacity;
} stack;

typedef struct _node {
    int value;
    struct _node* next;
} node;

stack* create_stack();

void print_stack(stack* pointer);

int push(stack* pointer, int value);

int pop(stack* pointer);

node* top(stack* pointer);

bool is_empty(stack* pointer);

int get_size(stack* pointer);

int clear_stack(stack* pointer);

int free_stack(stack* pointer);

#endif