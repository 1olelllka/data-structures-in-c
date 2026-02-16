#ifndef MAX_HEAP

#define MAX_HEAP
#include <stddef.h>


typedef struct _max_heap {
    int* data;
    size_t size;
    size_t capacity;
} max_heap;

max_heap* create_heap(size_t capacity);

int peek(max_heap* heap);

int push(max_heap* heap, int value);

int pop(max_heap* heap);

int free_heap(max_heap* heap);

int increase_key(max_heap* heap, size_t i, int value);

int decrease_key(max_heap* heap, size_t i, int value);

int remove_by_index(max_heap* heap, size_t i);

size_t get_size(max_heap* heap);

max_heap* heapify(int* arr, size_t size);

void print_heap(max_heap* heap);

#endif