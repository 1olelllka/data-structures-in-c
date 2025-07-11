#include "../include/doubly_linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    printf("Testing create doubly linked list...\n");
    linked_list* list = create_list();
    assert(list != NULL);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(list->size == 0);
    printf("OK.\n");

    printf("Testing insert at head of doubly linked list...\n");
    insert_head(list, 1);
    insert_head(NULL, 1);
    assert(list->size == 1);
    assert(list->head->value == 1);
    assert(list->tail->value == 1);
    assert(list->tail->prev == NULL);
    assert(list->tail->next == NULL);
    assert(list->head->prev == NULL);
    assert(list->head->next == NULL);
    print_as_string_forward(list);
    insert_head(list, 2);
    assert(list->size == 2);
    assert(list->head->value == 2);
    assert(list->head->next->value == 1);
    assert(list->head->next->prev->value == 2);
    assert(list->tail->value == 1);
    assert(list->tail->next == NULL);
    assert(list->tail->prev->value == 2);
    print_as_string_forward(list);
    printf("OK.\n");
    
    printf("Testing insert at tail of doubly linked list...\n");
    insert_tail(list, 3);
    insert_tail(NULL, 3);
    assert(list->size == 3);
    assert(list->head->value == 2);
    assert(list->head->prev == NULL);
    assert(list->head->next->value == 1);
    assert(list->head->next->next->value == 3);
    assert(list->head->next->next->prev->value == 1);
    assert(list->tail->value == 3);
    assert(list->tail->prev->value == 1);
    assert(list->tail->prev->prev->value == 2);
    print_as_string_forward(list);
    printf("OK.\n");

    printf("Testing insert at position of doubly linked list...\n");
    insert_position(list, 2, 4);
    insert_position(NULL, 2, 4);
    assert(list->size == 4);
    assert(list->head->value == 2);
    assert(list->head->next->value == 1);
    assert(list->head->next->prev->value == 2);
    assert(list->head->next->next->value == 4);
    assert(list->head->next->next->prev->value == 1);
    assert(list->head->next->next->next->value == 3);
    assert(list->tail->value == 3);
    assert(list->tail->prev->value == 4);
    assert(list->tail->prev->prev->value == 1);
    assert(list->tail->prev->prev->prev->value == 2);
    print_as_string_forward(list);
    print_as_string_backward(list);
    printf("OK.\n");

    printf("Testing head removal in doubly linked list...\n");
    remove_head(list);
    remove_head(NULL);
    assert(list->size == 3);
    assert(list->head->prev == NULL);
    assert(list->head->value == 1);
    assert(list->head->next->value == 4);
    print_as_string_forward(list);
    printf("OK.\n");

    printf("Testing tail removal in doubly linked list...\n");
    remove_tail(list);
    remove_tail(NULL);
    assert(list->size == 2);
    assert(list->tail->value == 4);
    assert(list->tail->next == NULL);
    assert(list->tail->prev->value == 1);
    print_as_string_forward(list);
    printf("OK.\n");

    printf("Testing position removal in doubly linked list...\n");
    insert_tail(list, 3);
    remove_by_index(list, 1);
    remove_by_index(NULL, 1);
    assert(list->size == 2);
    assert(list->head->next->value == 3);
    assert(list->head->next->prev->value == 1);
    assert(list->tail->prev->value == 1);
    print_as_string_forward(list);
    printf("OK.\n");

    printf("Testing value (first occurence) removal in doubly linked list...\n");
    insert_tail(list, 3);
    print_as_string_forward(list);
    remove_by_value(list, 3);
    assert(list->size == 2);
    assert(list->head->value == 1);
    assert(list->tail->value == 3);
    assert(list->tail->prev->value == 1);
    assert(list->head->next->value == 3);
    assert(list->head->next->next == NULL);
    print_as_string_forward(list);
    remove_by_value(list, 13413);
    remove_by_value(NULL, 1324);
    printf("OK.\n");

    printf("Getting size of doubly linked list...\n");
    assert(get_size(list) == list->size);
    get_size(NULL);
    printf("OK.\n");

    printf("Checkig if doubly linked list is empty...\n");
    assert(is_empty(list) == false);
    is_empty(NULL);
    printf("OK.\n");

    printf("Getting index of specific value in doubly linked list...\n");
    assert(index_of(list, 3) == 1);
    assert(index_of(NULL, 1) == -1);
    assert(index_of(list, 123) == -1);
    printf("OK.\n");

    printf("Checkig if doubly linked list contains specific value...\n");
    assert(contains(list, 3) == true);
    assert(contains(NULL, 3) == false);
    assert(contains(list, 123) == false);
    printf("OK.\n");

    printf("Testing updating the value on specific position in doubly linked list...\n");
    update_by_index(list, 1, 5);
    update_by_index(list, 1234, 1324);
    update_by_index(list, -1, 234);
    update_by_index(NULL, 1, 1);
    assert(list->tail->value == 5);
    assert(list->head->next->value == 5);
    printf("OK.\n");

    printf("Testing reversed doubly linked list...\n");
    insert_tail(list, 6);
    insert_tail(list, 7);
    linked_list* reversed = reverse_list(list);
    assert(reversed->head->value == 7);
    assert(reversed->head->prev == NULL);
    assert(reversed->head->next->value == 6);
    assert(reversed->head->next->prev->value == 7);
    assert(reversed->head->next->next->value == 5);
    assert(reversed->head->next->next->prev->value == 6);
    assert(reversed->head->next->next->next->value == 1);
    assert(reversed->head->next->next->next->prev->value == 5);
    assert(reversed->tail->value == 1);
    assert(reversed->tail->next == NULL);
    assert(reversed->tail->prev->value == 5);
    print_as_string_forward(reversed);
    print_as_string_backward(reversed);
    printf("OK.\n");

    printf("Free allocated memory...\n");
    free_list(list);
    printf("OK.\n");
}