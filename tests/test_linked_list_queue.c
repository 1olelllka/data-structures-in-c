#include "../include/linked_list_queue.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main(void) {

    printf("Creating linked list queue...\n");
    queue* q = create_queue();
    assert(q != NULL);
    print_queue(q);
    printf("OK.\n");

    printf("Testing enqueue...\n");
    assert(enqueue(NULL, 1234) == EXIT_FAILURE);
    assert(enqueue(q, 1) == EXIT_SUCCESS);
    print_queue(q);
    assert(enqueue(q, 2) == EXIT_SUCCESS);
    print_queue(q);
    assert(enqueue(q, 3) == EXIT_SUCCESS);
    print_queue(q);
    assert(enqueue(q, 4) == EXIT_SUCCESS);
    print_queue(q);
    assert(enqueue(q, 5) == EXIT_SUCCESS);
    print_queue(q);
    printf("OK.\n");

    printf("Testing dequeue...\n");
    assert(dequeue(NULL, NULL) == EXIT_FAILURE);
    int out;
    assert(dequeue(q, &out) == EXIT_SUCCESS);
    assert(out == 1);
    print_queue(q);
    assert(dequeue(q, &out) == EXIT_SUCCESS);
    assert(out == 2);
    print_queue(q);
    assert(dequeue(q, &out) == EXIT_SUCCESS);
    assert(out == 3);
    print_queue(q);
    assert(dequeue(q, &out) == EXIT_SUCCESS);
    assert(out == 4);
    print_queue(q);
    assert(dequeue(q, NULL) == EXIT_FAILURE);
    assert(dequeue(q, &out) == EXIT_SUCCESS);
    assert(out == 5);
    print_queue(q);
    assert(dequeue(q, &out) == EXIT_FAILURE);
    print_queue(q);
    printf("OK.\n");

    printf("Checking if empty...\n");
    assert(is_empty(NULL) == true);
    assert(is_empty(q) == true);
    assert(enqueue(q, 1) == EXIT_SUCCESS);
    assert(is_empty(q) == false);
    printf("OK.\n");

    printf("Getting peek...\n");
    assert(peek(NULL) == NULL);
    node* p = peek(q);
    assert(p != NULL);
    assert(p->value == 1);
    assert(enqueue(q, 2) == EXIT_SUCCESS);
    p = peek(q);
    assert(p != NULL);
    assert(p->value == 1);
    printf("OK.\n");

    printf("Getting rear...\n");
    assert(rear(NULL) == NULL);
    node* r = rear(q);
    assert(r != NULL);
    assert(r->value == 2);
    assert(enqueue(q, 3) == EXIT_SUCCESS);
    r = rear(q);
    assert(r->value == 3);
    printf("OK.\n");

    printf("Getting size...\n");
    assert(get_size(NULL) == 0);
    assert(get_size(q) == 3);
    printf("OK.\n");

    printf("Clearing the queue...\n");
    assert(clear_queue(NULL) == EXIT_FAILURE);
    assert(clear_queue(q) == EXIT_SUCCESS);
    assert(get_size(q) == 0);
    print_queue(q);
    printf("OK.\n");
    
    printf("Freeing allocated memory...\n");
    assert(enqueue(q, 1) == EXIT_SUCCESS);
    assert(enqueue(q, 2) == EXIT_SUCCESS);
    assert(enqueue(q, 3) == EXIT_SUCCESS);
    assert(enqueue(q, 4) == EXIT_SUCCESS);
    assert(enqueue(q, 5) == EXIT_SUCCESS);
    assert(get_size(q) == 5);
    int status = free_queue(q);
    assert(status == EXIT_SUCCESS);
    status = free_queue(NULL);
    assert(status == EXIT_FAILURE);
    printf("OK.\n");

    return EXIT_SUCCESS;
}