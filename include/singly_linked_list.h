#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node {
    int value;
    struct _node* next;
} node;

typedef struct _linked_list {
    int size;
    struct _node* head;
} linked_list;

linked_list* create_list();

void free_list(linked_list* list);

void insert_head(linked_list* list, int value);

void insert_tail(linked_list* list, int value);

void insert_position(linked_list* list, int position, int value);

void remove_head(linked_list* list);

void remove_tail(linked_list* list);

void remove_by_index(linked_list* list, int index);

void remove_by_value(linked_list* list, int value);

bool contains(linked_list* list, int value);

int index_of(linked_list* list, int value);

int is_empty(linked_list* list);

int get_size(linked_list* list);

void update_by_index(linked_list* list, int index, int value);

linked_list* reverse_list(linked_list* list);

void print_as_string(linked_list *list);

#endif