#include "../include/array_stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#define INIT_SIZE 5

stack* create_stack(int capacity) {
    if (capacity <= 0) {
        printf("Error: you must enter a capacity greater than 0.\n");
        return NULL;
    }
    stack* new_stack = malloc(sizeof(stack));
    new_stack->values = malloc(sizeof(int) * capacity);
    new_stack->capacity = capacity;
    new_stack->size = 0;
    return new_stack;
}

int push(stack* pointer, int value) {
    if (pointer == NULL) return EXIT_FAILURE;
    if (pointer->size == pointer->capacity) {
        int* tmp = realloc(pointer->values, sizeof(int) * pointer->capacity * 2);
        if (tmp == NULL) {
            perror("ERROR WHILE REALLOCATING");
            return EXIT_FAILURE;
        }
        pointer->values = tmp;
        pointer->capacity = pointer->capacity * 2;
    }
    pointer->values[pointer->size] = value;
    pointer->size += 1;
    return EXIT_SUCCESS;
}

int pop(stack* pointer) {
    if (pointer == NULL) return INT_MIN;
    if (pointer->size == 0) return INT_MIN;
    int val = pointer->values[pointer->size - 1];
    pointer->size -= 1;
    if (pointer->capacity > INIT_SIZE && pointer->size <= pointer->capacity / 4) {
        int new_capacity = pointer->capacity / 2;
        if (new_capacity < INIT_SIZE) new_capacity = INIT_SIZE;
        int* temp = realloc(pointer->values, sizeof(int) * new_capacity);
        if (temp == NULL) {
            perror("ERROR WHILE REALLOCATING");
            return EXIT_FAILURE;
        }
        pointer->values = temp;
        pointer->capacity = new_capacity;
    }
    return val;
}

int top(stack* pointer) {
    if (pointer == NULL) return INT_MIN;
    if (pointer->size == 0) return INT_MIN;
    return pointer->values[pointer->size - 1];
}

int get_size(stack* pointer) {
    if (pointer == NULL) return INT_MIN;
    return pointer->size;
}

bool is_empty(stack* pointer) {
    if (pointer == NULL) return true;
    return pointer->size == 0;
}

int clear_stack(stack* pointer) {
    if (pointer == NULL) return EXIT_FAILURE;
    pointer->size = 0;
    int* tmp = realloc(pointer->values, sizeof(int) * INIT_SIZE);
    if (tmp == NULL) {
         perror("ERROR WHILE REALLOCATING");
        return EXIT_FAILURE;
    }
    pointer->values = tmp;
    pointer->capacity = INIT_SIZE;
    memset(pointer->values, 0, sizeof(int) * pointer->capacity);
    return EXIT_SUCCESS;
}

void print_stack(stack* pointer) {
    printf("\n     TOP\n");
    if (pointer == NULL || pointer->capacity == 0) {
        printf(" -----------\n");
        printf("|   NULL    |\n");
        printf(" -----------\n");
        return;
    }
    for (int i = 0; i < pointer->capacity - pointer->size; i++) {
        printf(" -----------\n");
        printf("|   FREE    |\n");
    }
    for (int i = 0; i < pointer->size; i++) {
        printf(" -----------\n");
        printf("|     %d     |\n", pointer->values[pointer->size - i - 1]);
    }
    printf(" -----------\n");
}

int free_stack(stack* pointer) {
    if (pointer == NULL) return EXIT_FAILURE;
    free(pointer->values);
    free(pointer);
    return EXIT_SUCCESS;
}