#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST
#include <stdbool.h>

typedef struct _node {
    int value;
    struct _node* next;
    struct _node* prev;
} node;

typedef struct _linked_list {
    struct _node* head;
    struct _node* tail;
    int size;
} linked_list;

linked_list* create_list();

void free_list(linked_list* list);

void insert_head(linked_list* list, int value);

void insert_tail(linked_list* list, int value);

void insert_position(linked_list* list, int position, int value);

void remove_head(linked_list* list);

void remove_tail(linked_list* list);

void remove_by_index(linked_list* list, int position);

void remove_by_value(linked_list* list, int value);

int get_size(linked_list* list);

bool is_empty(linked_list* list);

int index_of(linked_list* list, int value);

bool contains(linked_list* list, int value);

void update_by_index(linked_list* list, int position, int value);

linked_list* reverse_list(linked_list* list);

void print_as_string_forward(linked_list* list);

void print_as_string_backward(linked_list* list);

#endif