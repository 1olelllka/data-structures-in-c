#ifndef LINKED_QUEUE

#define LINKED_QUEUE
#include <stdbool.h>

typedef struct _queue {
    struct _node* head;
    struct _node* tail;
    int size;
} queue;

typedef struct _node {
    int value;
    struct _node* next;
} node;

queue* create_queue();

int enqueue(queue* pointer, int value);

int dequeue(queue* pointer, int* value);

node* peek(queue* pointer);

node* rear(queue* pointer);

bool is_empty(queue* pointer);

int get_size(queue* pointer);

int clear_queue(queue* pointer);

void print_queue(queue* pointer);

int free_queue(queue* pointer);

#endif