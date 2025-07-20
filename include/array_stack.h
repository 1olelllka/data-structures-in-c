#ifndef ARRAY_STACK

#define ARRAY_STACK
#include <stdbool.h>

typedef struct _stack {
    int* values;
    int size;
    int capacity;
} stack;

stack* create_stack(int capacity);

void print_stack(stack* pointer);

int push(stack* pointer, int value);

int pop(stack* pointer);

int top(stack* pointer);

bool is_empty(stack* pointer);

int get_size(stack* pointer);

int clear_stack(stack* pointer);

int free_stack(stack* pointer);

#endif