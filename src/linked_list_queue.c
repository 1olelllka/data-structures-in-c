#include "../include/linked_list_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

queue* create_queue() {
    queue* new_queue = malloc(sizeof(queue));
    if (new_queue == NULL) {
        perror("ERROR malloc()");
        return NULL;
    }
    new_queue->size = 0;
    new_queue->head = NULL;
    new_queue->tail = NULL;
    return new_queue;
}

int enqueue(queue* pointer, int value) {
    if (pointer == NULL) return EXIT_FAILURE;
    node* new_elem = malloc(sizeof(node));
    if (new_elem == NULL) {
        perror("ERROR malloc()");
        return EXIT_FAILURE;
    }
    new_elem->value = value;
    new_elem->next = NULL;
    if (pointer->size == 0) {
        pointer->head = new_elem;
        pointer->tail = new_elem;
    } else {
        pointer->tail->next = new_elem;
        pointer->tail = new_elem;
    }
    pointer->size += 1;
    return EXIT_SUCCESS;
}

int dequeue(queue* pointer, int* val) {
    if (pointer == NULL) return EXIT_FAILURE;
    if (val == NULL) return EXIT_FAILURE;
    if (pointer->head == NULL) return EXIT_FAILURE;
    if (pointer->tail == NULL) return EXIT_FAILURE;
    if (pointer->size == 1) {
        *val = pointer->head->value;
        free(pointer->head);
        pointer->head = NULL;
        pointer->tail = NULL;
    } else {
        node* tmp = pointer->head;
        pointer->head = pointer->head->next;
        *val = tmp->value;
        free(tmp);
    }
    pointer->size -= 1;
    return EXIT_SUCCESS;
}

node* peek(queue* pointer) {
    if (pointer == NULL) return NULL;
    return pointer->head;
}

node* rear(queue* pointer) {
    if (pointer == NULL) return NULL;
    return pointer->tail;
}

bool is_empty(queue* pointer) {
    if (pointer == NULL) return true;
    return pointer->size == 0;
}

int get_size(queue* pointer) {
    if (pointer == NULL) return 0;
    return pointer->size;
}

int clear_queue(queue* pointer) {
    if (pointer == NULL) return EXIT_FAILURE;
    node* dummy = pointer->head;
    while (dummy) {
        node* tmp = dummy;
        dummy = dummy->next;
        free(tmp);
    }
    pointer->head = NULL;
    pointer->tail = NULL;
    pointer->size = 0;
    return EXIT_SUCCESS;
}

void print_queue(queue* pointer) {
    if (pointer == NULL) return;
    node* dummy = pointer->head;
    printf("HEAD: -> ");
    while (dummy) {
        printf("( %d ) -> ", dummy->value);
        dummy = dummy->next;
    }
    printf(":TAIL\n");
}

int free_queue(queue* pointer) {
    if (pointer == NULL) return EXIT_FAILURE;
    queue* to_free = pointer;
    clear_queue(pointer);
    free(to_free);
    return EXIT_SUCCESS;
}