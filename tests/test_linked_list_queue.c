#include "../include/linked_list_queue.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void print_int(void* val) {
    printf("(%d)", *(int*)val);
}

void print_str(void* val) {
    printf("(%s)", (char*)(val));
}

int main(void) {
    printf("Creating linked list queue...\n");
    queue* q = create_queue();
    assert(q != NULL);
    print_queue(q, &print_int);
    printf("OK.\n");

    printf("Testing enqueue...\n");
    int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5;
    assert(enqueue(NULL, &v1) == EXIT_FAILURE);
    assert(enqueue(q, &v1) == EXIT_SUCCESS);
    print_queue(q, &print_int);
    assert(enqueue(q, &v2) == EXIT_SUCCESS);
    print_queue(q, &print_int);
    assert(enqueue(q, &v3) == EXIT_SUCCESS);
    print_queue(q, &print_int);
    assert(enqueue(q, &v4) == EXIT_SUCCESS);
    print_queue(q, &print_int);
    assert(enqueue(q, &v5) == EXIT_SUCCESS);
    print_queue(q, &print_int);
    printf("OK.\n");

    printf("Testing dequeue...\n");
    assert(dequeue(NULL, NULL) == EXIT_FAILURE);
    void* out;
    assert(dequeue(q, &out) == EXIT_SUCCESS);
    assert(*(int*)out == 1);
    print_queue(q, &print_int);
    assert(dequeue(q, &out) == EXIT_SUCCESS);
    assert(*(int*)out == 2);
    print_queue(q, &print_int);
    assert(dequeue(q, &out) == EXIT_SUCCESS);
    assert(*(int*)out == 3);
    print_queue(q, &print_int);
    assert(dequeue(q, &out) == EXIT_SUCCESS);
    assert(*(int*)out == 4);
    print_queue(q, &print_int);
    assert(dequeue(q, NULL) == EXIT_FAILURE);
    assert(dequeue(q, &out) == EXIT_SUCCESS);
    assert(*(int*)out == 5);
    print_queue(q, &print_int);
    assert(dequeue(q, &out) == EXIT_FAILURE);
    print_queue(q, &print_int);
    printf("OK.\n");

    printf("Checking if empty...\n");
    assert(is_empty(NULL) == true);
    assert(is_empty(q) == true);
    assert(enqueue(q, &v1) == EXIT_SUCCESS);
    assert(is_empty(q) == false);
    printf("OK.\n");

    printf("Getting peek...\n");
    assert(peek(NULL) == NULL);
    node* p = peek(q);
    assert(p != NULL);
    assert(*(int*)p->value == 1);
    assert(enqueue(q, &v2) == EXIT_SUCCESS);
    p = peek(q);
    assert(p != NULL);
    assert(*(int*)p->value == 1);
    printf("OK.\n");

    printf("Getting rear...\n");
    assert(rear(NULL) == NULL);
    node* r = rear(q);
    assert(r != NULL);
    assert(*(int*)r->value == 2);
    assert(enqueue(q, &v3) == EXIT_SUCCESS);
    r = rear(q);
    assert(*(int*)r->value == 3);
    printf("OK.\n");

    printf("Getting size...\n");
    assert(get_size(NULL) == 0);
    assert(get_size(q) == 3);
    printf("OK.\n");

    printf("Clearing the queue...\n");
    assert(clear_queue(NULL) == EXIT_FAILURE);
    assert(clear_queue(q) == EXIT_SUCCESS);
    assert(get_size(q) == 0);
    print_queue(q, &print_int);
    printf("OK.\n");

    printf("Testing enqueue with strings...\n");
    char* str1 = "ABC";
    char* str2 = "DEF";
    char* str3 = "XYZ";
    assert(enqueue(q, str1) == EXIT_SUCCESS);
    assert(enqueue(q, str2) == EXIT_SUCCESS);
    assert(enqueue(q, str3) == EXIT_SUCCESS);
    print_queue(q, &print_str);
    printf("OK.\n");

    printf("Freeing allocated memory...\n");
    assert(get_size(q) == 3);
    int status = free_queue(q);
    assert(status == EXIT_SUCCESS);
    status = free_queue(NULL);
    assert(status == EXIT_FAILURE);
    printf("OK.\n");

    return EXIT_SUCCESS;
}