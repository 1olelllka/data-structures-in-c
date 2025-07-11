#include "../include/singly_linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    linked_list* list = create_list();
    printf("Testing create singly linked list...\n");
    assert(list != NULL);
    assert(list->size == 0);
    assert(list->head == NULL);
    printf("OK.\n");

    printf("Testing insert to the head of singly linked list...\n");
    insert_head(list, 10);
    assert(list->size == 1);
    assert(list->head->value == 10);
    insert_head(list, 20);
    insert_head(NULL, 10);
    assert(list->size == 2);
    assert(list->head->value == 20);
    assert(list->head->next->value == 10);
    assert(list->head->next->next == NULL);
    print_as_string(list);
    printf("OK.\n");

    printf("Testing insert to the tail of singly linked list...\n");
    insert_tail(list, 30);
    assert(list->size == 3);
    assert(list->head->next->next->value == 30);
    insert_tail(list, 40);
    insert_tail(NULL, 500);
    assert(list->size == 4);
    assert(list->head->next->next->next->value == 40);
    assert(list->head->next->next->next->next == NULL);
    print_as_string(list);
    printf("OK.\n");

    printf("Testing insert to the specific position of singly linked list...\n");
    insert_position(list, 2, 100);
    insert_position(NULL, 2, 100);
    assert(list->size == 5);
    assert(list->head->value == 20);
    assert(list->head->next->value == 10);
    assert(list->head->next->next->value == 100);
    assert(list->head->next->next->next->value == 30);
    assert(list->head->next->next->next->next->value == 40);
    insert_position(list, 200, 200);
    assert(list->size == 5);
    print_as_string(list);
    printf("OK.\n");

    printf("Testing update the value on specific index of singly linked list...\n");
    update_by_index(list, 1, 200);
    update_by_index(NULL, 1, 200);
    assert(list->size == 5);
    assert(list->head->value == 20);
    assert(list->head->next->value == 200);
    update_by_index(list, 100, 100);
    assert(list->size == 5);
    print_as_string(list);
    printf("OK.\n");

    printf("Testing getting size of singly linked list...\n");
    assert(get_size(list) == 5);
    assert(get_size(NULL) == 0);
    printf("OK.\n");
    
    printf("Testing checking if empty singly linked list...\n");
    assert(is_empty(list) == false);
    assert(is_empty(NULL) == true);
    printf("OK.\n");

    printf("Testing contains function of singly linked list...\n");
    assert(contains(list, 100) == true);
    assert(contains(list, 500) == false);
    assert(contains(NULL, 100) == false);
    printf("OK.\n");

    printf("Testing index search of singly linked list...\n");
    assert(index_of(list, 100) == 2);
    assert(index_of(NULL, 100) == -1);
    printf("OK\n");

    printf("Testing head removal in singly linked list...\n");
    remove_head(list);
    remove_head(NULL);
    assert(list->size == 4);
    assert(list->head->value == 200);
    assert(list->head->next->value == 100);
    assert(contains(list, 20) == false);
    print_as_string(list);
    printf("OK.\n");

    printf("Testing tail removal in singly linked list...\n");
    remove_tail(list);
    remove_tail(NULL);
    assert(list->size == 3);
    assert(list->head->next->next->value == 30);
    assert(list->head->next->next->next == NULL);
    assert(contains(list, 40) == false);
    print_as_string(list);
    printf("OK.\n");

    printf("Testing position removal in singly linked list...\n");
    remove_by_index(list, 1);
    remove_by_index(NULL, 1);
    assert(list->size == 2);
    assert(list->head->next->next == NULL);
    assert(list->head->next->value == 30);
    assert(contains(list, 100) == false);
    remove_by_index(list, 100);
    assert(list->size == 2);
    print_as_string(list);
    printf("OK.\n");

    printf("Testing value removal (first occurence) in singly linked list...\n");
    insert_tail(list, 200);
    remove_by_value(list, 200);
    remove_by_value(NULL, 200);
    assert(list->size == 2);
    assert(list->head->value == 30);
    assert(list->head->next->value == 200);
    assert(list->head->next->next == NULL);
    assert(contains(list, 200) == true);
    print_as_string(list);
    printf("OK.\n");


    printf("Testing linked list reverse...\n");
    insert_head(list, 1);
    insert_tail(list, 2);
    print_as_string(list);
    linked_list* reversed = reverse_list(list);
    assert(reversed->head->value == 2);
    assert(reversed->head->next->value == 200);
    assert(reversed->head->next->next->value == 30);
    assert(reversed->head->next->next->next->value == 1);
    printf("Reversed ");
    print_as_string(reversed);
    assert(reverse_list(NULL) == NULL); 
    printf("OK.\n");

    printf("Free allocated memory...\n");
    free_list(list);
    printf("OK.\n");
    return EXIT_SUCCESS;
}