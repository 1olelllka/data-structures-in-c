#include "../include/max_heap.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

max_heap* create_heap(size_t capacity) {
    if (capacity <= 0) {
        printf("Error: Heap capacity cannot be less or equal to zero.\n");
        return NULL;
    }
    max_heap* heap = malloc(sizeof(max_heap));
    if (heap == NULL) {
        perror("Error allocating memory for heap");
        return NULL;
    }
    heap->capacity = capacity;
    heap->size = 0;
    heap->data = malloc(sizeof(int) * (heap->capacity + 1));
    if (heap->data == NULL) {
        perror("Error allocating memory for heap's data");
        free(heap);
        return NULL;
    }
    return heap;
}

void print_heap(max_heap* heap) {
    if (!heap || heap->size == 0) {
        printf("(empty heap)\n");
        return;
    }

    size_t level = 0;
    size_t elements_in_level = 1;
    size_t printed = 0;

    for (size_t i = 1; i <= heap->size; i++) {
        printf("%d ", heap->data[i]);
        printed++;

        if (printed == elements_in_level) {
            printf("\n");
            level++;
            elements_in_level <<= 1;
            printed = 0;
        }
    }

    if (printed != 0) {
        printf("\n");
    }
}

void heapify_up(max_heap* heap, int idx) {
    if (heap->size == 1) return;
    int i = idx;
    int parent = i / 2;
    while (i > 1) {
        if (heap->data[i] > heap->data[parent]) {
            int tmp = heap->data[i];
            heap->data[i] = heap->data[parent];
            heap->data[parent] = tmp;
        }
        i /= 2;
        parent /= 2;
    }
}

int push(max_heap* heap, int value) {
    if (heap == NULL) return EXIT_FAILURE;
    if (heap->data == NULL) return EXIT_FAILURE;
    if (heap->size == heap->capacity) return EXIT_FAILURE;
    *(heap->data + heap->size + 1) = value;
    heap->size += 1;
    heapify_up(heap, heap->size);
    return EXIT_SUCCESS;
}

void heapify_down(max_heap* heap, size_t i) {
    if (heap->size == 1) return;
    while (2 * i <= heap->size) {
        if (2 * i + 1 <= heap->size && heap->data[2 * i + 1] > heap->data[2 * i] && heap->data[i] < heap->data[2 * i + 1]) {
            int tmp = heap->data[i];
            heap->data[i] = heap->data[2 * i + 1];
            heap->data[2 * i + 1] = tmp;
            i = 2 * i + 1;
        } else if (heap->data[2 * i] > heap->data[i]) {
            int tmp = heap->data[i];
            heap->data[i] = heap->data[2 * i];
            heap->data[2 * i] = tmp;
            i = 2 * i;
        } else break;
    }
}

int pop(max_heap* heap) {
    if (heap == NULL) return INT_MIN;
    if (heap->data == NULL) return INT_MIN;
    if (heap->size == 0) return INT_MIN;
    int popped = *(heap->data + 1);
    *(heap->data + 1) = heap->data[heap->size];
    heapify_down(heap, 1);
    heap->size -= 1;
    return popped;
}

int peek(max_heap* heap) {
    if (heap == NULL) return INT_MIN;
    if (heap->data == NULL) return INT_MIN;
    if (heap->size == 0) return INT_MIN;
    return *(heap->data + 1);
}

int increase_key(max_heap* heap, size_t i, int value) {
    if (heap == NULL) return EXIT_FAILURE;
    if (heap->data == NULL) return EXIT_FAILURE;
    if (i >= heap->size) return EXIT_FAILURE;
    if (value < 0) return EXIT_FAILURE;
    if (value == 0) return EXIT_SUCCESS;
    heap->data[i + 1] += value;
    heapify_up(heap, i + 1);
    return EXIT_SUCCESS;
}

int decrease_key(max_heap* heap, size_t i, int value) {
    if (heap == NULL) return EXIT_FAILURE;
    if (heap->data == NULL) return EXIT_FAILURE;
    if (i >= heap->size) return EXIT_FAILURE;
    if (value < 0) return EXIT_FAILURE;
    if (value == 0) return EXIT_SUCCESS;
    heap->data[i + 1] -= value;
    heapify_down(heap, i + 1);
    return EXIT_SUCCESS;
}

int remove_by_index(max_heap* heap, size_t i) {
    if (heap == NULL) return EXIT_FAILURE;
    if (heap->data == NULL) return EXIT_FAILURE;
    if (i >= heap->size) return EXIT_FAILURE;
    heap->data[i + 1] = heap->data[heap->size];
    heapify_down(heap, i + 1);
    heap->size -= 1;
    return EXIT_SUCCESS;
}

max_heap* heapify(int* arr, size_t size) {
    if (arr == NULL) return NULL;
    if (size == 0) return NULL;
    max_heap* heap = create_heap(size);
    memcpy(heap->data, arr, size * sizeof(int));
    heap->size = size;
    heap->data[size] = heap->data[0];
    int curr = heap->size / 2;
    while (curr > 0) {
        int i = curr;
        heapify_down(heap, i);
        curr -= 1;
    }
    return heap;
}

size_t get_size(max_heap* heap) {
    if (heap == NULL) return 0;
    return heap->size;
}

int free_heap(max_heap* heap) {
    if (heap == NULL) return EXIT_FAILURE;
    free(heap->data);
    free(heap);
    return EXIT_SUCCESS;
}