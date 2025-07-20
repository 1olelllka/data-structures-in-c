#include "../include/linked_list_stack.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    printf("Creating new dynamic stack...\n");
    stack* new_stack = create_stack(5);
    assert(new_stack != NULL);
    print_stack(new_stack);
    printf("OK.\n");

    printf("Pushing the values into the stack...\n");
    assert(push(new_stack, 1) == EXIT_SUCCESS);
    print_stack(new_stack);
    assert(push(new_stack, 2) == EXIT_SUCCESS);
    print_stack(new_stack);
    assert(push(new_stack, 3) == EXIT_SUCCESS);
    print_stack(new_stack);
    assert(push(new_stack, 4) == EXIT_SUCCESS);
    print_stack(new_stack);
    assert(push(new_stack, 5) == EXIT_SUCCESS);
    print_stack(new_stack);
    assert(push(NULL, 1) == EXIT_FAILURE);
    printf("OK.\n");

    printf("Popping the values from the stack...\n");
    assert(pop(new_stack) == 5);
    print_stack(new_stack);
    assert(pop(new_stack) == 4);
    print_stack(new_stack);
    assert(pop(new_stack) == 3);
    print_stack(new_stack);
    assert(pop(new_stack) == 2);
    print_stack(new_stack);
    assert(pop(new_stack) == 1);
    print_stack(new_stack);
    assert(pop(NULL) == EXIT_FAILURE);
    printf("OK.\n");

    printf("Checking if the stack is empty...\n");
    assert(is_empty(new_stack) == true);
    push(new_stack, 1);
    assert(is_empty(new_stack) == false);
    printf("OK.\n");

    printf("Checking the length of the stack...\n");
    assert(get_size(new_stack) == 1);
    push(new_stack, 2);
    push(new_stack, 2);
    push(new_stack, 2);
    push(new_stack, 2);
    pop(new_stack);
    pop(new_stack);
    push(new_stack, 4);
    assert(get_size(new_stack) == 4);
    printf("OK.\n");

    printf("Getting the top of the stack...\n");
    node* tmp = top(new_stack);
    assert(tmp->value == 4);
    tmp = top(NULL);
    assert(tmp == NULL);
    printf("OK.\n");

    printf("Clearing the stack...\n");
    assert(clear_stack(new_stack) == EXIT_SUCCESS);
    assert(is_empty(new_stack) == true);
    assert(get_size(new_stack) == 0);
    assert(top(new_stack) == NULL);
    printf("OK.\n");
    
    printf("Freeing allocated memory...\n");
    free_stack(new_stack);
    printf("OK.\n");
    return EXIT_SUCCESS;
}