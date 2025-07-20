#include "../include/array_stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void) {
    printf("Testing create static stack...\n");
    stack* s = create_stack(5);
    assert(s != NULL);
    assert(s->capacity == 5);
    assert(s->size == 0);
    printf("OK.\n");

    printf("Testing pushing to the static stack...\n");
    assert(push(NULL, 1) == EXIT_FAILURE);
    print_stack(s);
    assert(push(s, 1) == EXIT_SUCCESS);
    print_stack(s);
    assert(push(s, 2) == EXIT_SUCCESS);
    print_stack(s);
    assert(push(s, 3) == EXIT_SUCCESS);
    print_stack(s);
    assert(push(s, 4) == EXIT_SUCCESS);
    print_stack(s);
    assert(push(s, 5) == EXIT_SUCCESS);
    print_stack(s);
    // Resized
    assert(push(s, 6) == EXIT_SUCCESS);
    print_stack(s);
    assert(s->values[0] == 1);
    assert(s->values[1] == 2);
    assert(s->values[2] == 3);
    assert(s->values[3] == 4);
    assert(s->values[4] == 5);
    printf("OK.\n");

    printf("Testing popping from the stack...\n");
    assert(pop(NULL) == INT_MIN);
    assert(pop(s) == 6);
    print_stack(s);
    assert(pop(s) == 5);
    print_stack(s);
    assert(pop(s) == 4);
    print_stack(s);
    assert(pop(s) == 3);
    print_stack(s);
    assert(pop(s) == 2);
    print_stack(s);
    printf("%d\n", s->capacity);
    assert(s->capacity == 5);
    printf("OK.\n");

    printf("Getting top of the stack...\n");
    assert(top(s) == 1);
    assert(top(NULL) == INT_MIN);
    printf("OK.\n");

    printf("Getting size of the stack...\n");
    assert(get_size(s) == 1);
    assert(get_size(NULL) == INT_MIN);
    printf("OK.\n");

    printf("Clearing the stack...\n");
    assert(clear_stack(s) == EXIT_SUCCESS);
    assert(get_size(s) == 0);
    assert(top(s) == INT_MIN);
    printf("OK.\n");

    printf("Checking emptiness of the stack...\n");
    assert(is_empty(NULL) == true);
    assert(is_empty(s) == true);
    printf("OK.\n");

    printf("Freeing allocated memory...\n");
    free_stack(s);
    printf("OK.\n");
    return EXIT_SUCCESS;
}