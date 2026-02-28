#ifndef LINKED_QUEUE

#define LINKED_QUEUE
#include <stdbool.h>

typedef struct _queue {
    struct _node* head;
    struct _node* tail;
    int size;
} queue;

typedef struct _node {
    void* value;
    struct _node* next;
} node;

queue* create_queue();

int enqueue(queue* pointer, void* value);

int dequeue(queue* pointer, void** value);

node* peek(queue* pointer);

node* rear(queue* pointer);

bool is_empty(queue* pointer);

int get_size(queue* pointer);

int clear_queue(queue* pointer);

void print_queue(queue* pointer, void (*func)(void*));

int free_queue(queue* pointer);

#endif