#include "../include/max_heap.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>

int main(void) {
    printf("Creating new max heap...\n");
    size_t size = 32;
    max_heap* heap = create_heap(size);
    assert(heap != NULL);
    print_heap(heap);
    printf("OK.\n");

    printf("Pushing different values to the max heap...\n");
    int test_values[32] = {
    45, 12, 78, 34, 23, 56, 89, 1,
    67, 90, 15, 3, 90, 27, 88, 42,
    33, 19, 71, 5, 62, 14, 81, 7,
    29, 55, 39, 8, 66, 13, 77, 20
    };
    for (int i = 0; i < 32; i++) {
        assert(push(heap, test_values[i]) == EXIT_SUCCESS);
    }
    assert(push(heap, 123) == EXIT_FAILURE);
    assert(peek(heap) == 90);
    assert(get_size(heap) == 32);
    print_heap(heap);
    printf("OK.\n");

    printf("Popping all of the values from the max heap...\n");
    assert(pop(heap) == 90);
    assert(pop(heap) == 90);
    for (int i = 0; i < 29; i++) {
        pop(heap);
    }
    assert(get_size(heap) == 1);
    printf("The last element: ");
    print_heap(heap);
    assert(pop(heap) == 1);
    printf("After deleting the last one: ");
    print_heap(heap);
    assert(get_size(heap) == 0);
    assert(pop(heap) == INT_MIN);
    printf("OK.\n");

    printf("Testing increasing the elements in the max heap...\n");
    assert(increase_key(heap, 123, 123) == EXIT_FAILURE);
    for (int i = 0; i < 32; i++) {
        assert(push(heap, test_values[i]) == EXIT_SUCCESS);
    }
    assert(increase_key(heap, 23, 1000) == EXIT_SUCCESS);
    printf("After increasing the 23rd element by 1000:\n");
    print_heap(heap);
    assert(peek(heap) == 1003);
    assert(increase_key(heap, 11, 12) == EXIT_SUCCESS);
    printf("After increasing the 11th element by 12:\n");
    print_heap(heap);
    assert(peek(heap) == 1003);
    printf("OK.\n");

    printf("Testing decreasing the elements in the max heap...\n");
    assert(decrease_key(heap, 12345, 123) == EXIT_FAILURE);
    assert(decrease_key(heap, 0, 1000) == EXIT_SUCCESS);
    print_heap(heap);
    printf("After decreasing the first element the peek value changes: %d\n", peek(heap));
    assert(peek(heap) == 90);
    assert(decrease_key(heap, 12, 5) == EXIT_SUCCESS);
    printf("After decreasing the 12th element by 5 the tree looks like:\n");
    print_heap(heap);
    printf("OK.\n");

    printf("Testing removing the elements on specific indexes...\n");
    assert(remove_by_index(heap, 123456) == EXIT_FAILURE);
    assert(remove_by_index(heap, 12) == EXIT_SUCCESS);
    assert(get_size(heap) == 31);
    assert(peek(heap) == 90);
    assert(heap->data[12] != 50); // 12th element validation
    printf("After removing the 12th element the tree looks like:\n");
    print_heap(heap);
    printf("OK.\n");

    printf("Testing the heapify function...\n");
    max_heap* arr_heap = heapify(test_values, 32);
    assert(arr_heap != NULL);
    assert(get_size(arr_heap) == 32);
    assert(peek(arr_heap) == 90);
    for (int i = 0; i < 31; i++) {
        pop(arr_heap);
    }
    assert(get_size(arr_heap) == 1);
    printf("The last element: ");
    print_heap(arr_heap);
    assert(pop(arr_heap) == 1);
    printf("After deleting the last one: ");
    print_heap(arr_heap);
    assert(get_size(arr_heap) == 0);
    printf("Freeing the heapify-based heap...\n");
    assert(free_heap(arr_heap) == EXIT_SUCCESS);
    printf("OK.\n");

    printf("Freeing allocated memory...\n");
    assert(free_heap(heap) == EXIT_SUCCESS);
    printf("OK.\n");

    return EXIT_SUCCESS;
}