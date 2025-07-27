#include "../include/linked_list_stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

stack* create_stack() {
    stack* new_stack = malloc(sizeof(stack));
    if (new_stack == NULL) {
        perror("ERROR CREATING STACK\n");
        return NULL;
    }
    new_stack->size = 0;
    new_stack->top = NULL;
    return new_stack;
}

void print_stack(stack* pointer) {
    printf("\n     TOP\n");
    if (pointer == NULL || pointer->top == NULL) {
        printf(" -----------\n");
        printf("|   NULL    |\n");
        printf(" -----------\n");
        return;
    }
    node* dummy = pointer->top;
    while (dummy) {
        printf(" -----------\n");
        printf("|     %d     |\n", dummy->value);
        dummy = dummy->next;
    }
    printf(" -----------\n");
}

// LIFO -- Last In First Out Principle
int push(stack* pointer, int value) {
    if (pointer == NULL) return EXIT_FAILURE;
    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        perror("ERROR PUSHING TO THE STACK");
        return EXIT_FAILURE;
    }
    new_node->value = value;
    new_node->next = NULL;
    node* tmp = pointer->top;
    pointer->top = new_node;
    pointer->top->next = tmp;
    pointer->size += 1;
    return EXIT_SUCCESS;
}

int pop(stack* pointer) {
    if (pointer == NULL) return EXIT_FAILURE;
    if (pointer->top == NULL) return EXIT_FAILURE;
    node* to_free = pointer->top;
    int res_val = to_free->value;
    pointer->top = pointer->top->next;
    pointer->size -= 1;
    free(to_free);
    return res_val;
}

node* top(stack* pointer) {
    if (pointer == NULL) return NULL;
    return pointer->top;
}

bool is_empty(stack* pointer) {
    if (pointer == NULL) return true;
    return pointer->size == 0;
}

int get_size(stack* pointer) {
    if (pointer == NULL) return 0;
    return pointer->size;
}

int clear_stack(stack* pointer) {
    if (pointer == NULL) return EXIT_FAILURE;
    node* dummy = pointer->top;
    while (dummy) {
        node* tmp = dummy;
        dummy = dummy->next;
        free(tmp);
    }
    pointer->top = NULL;
    pointer->size = 0;
    return EXIT_SUCCESS;
}

int free_stack(stack* pointer) {
    if (pointer == NULL) return EXIT_FAILURE;
    void* to_free = pointer;
    while (pointer->top) {
        void* tmp = pointer->top;
        pointer->top = pointer->top->next;
        free(tmp);
    }
    free(to_free);
    return EXIT_SUCCESS;
}