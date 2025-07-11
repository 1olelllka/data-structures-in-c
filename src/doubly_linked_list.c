#include "../include/doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

linked_list* create_list() {
    linked_list* list = malloc(sizeof(linked_list));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void insert_head(linked_list* list, int value) {
    if (list == NULL) return;
    node* new_node = malloc(sizeof(node));
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    if (list->size == 0) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->head->prev = new_node;
        node* tmp = list->head;
        list->head = new_node;
        list->head->next = tmp;
    }
    list->size += 1;
}

void insert_tail(linked_list* list, int value) {
    if (list == NULL) return;
    node* new_node = malloc(sizeof(node));
    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = NULL;
    if (list->size == 0) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        node* tmp = list->tail;
        list->tail = new_node;
        list->tail->prev = tmp;
    }
    list->size += 1;
}

void insert_position(linked_list* list, int position, int value) {
    if (list == NULL) return;
    if (list->size < position) return;
    if (position < 0) return;
    if (position == 0) {
        insert_head(list, value);
    } else if (position == list->size) {
        insert_tail(list, value);
    } else {
        node* new_node = malloc(sizeof(node));
        new_node->value = value;
        new_node->next = NULL;
        new_node->prev = NULL;
        node* dummy = list->head;
        for (int i = 1; i < position; i++) {
            dummy = dummy->next;
        }
        new_node->prev = dummy;
        node* tmp = dummy->next;
        dummy->next = new_node;
        tmp->prev = dummy->next;
        dummy->next->next = tmp;
        list->size += 1;
    }
}

void remove_head(linked_list* list) {
    if (list == NULL) return;
    if (list->head == NULL) return;
    if (list->size == 0) return;
    node* tmp = list->head;
    list->head = list->head->next;
    if (list->head) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }
    free(tmp);
    list->size -= 1;
}

void remove_tail(linked_list* list) {
    if (list == NULL) return;
    if (list->tail == NULL) return;
    if (list->size == 0) return;
    node* tmp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }
    free(tmp);
    list->size -= 1;
}

void remove_by_index(linked_list* list, int position) {
    if (list == NULL) return;
    if (list->size == 0) return;
    if (position < 0) return;
    if (position > list->size) return;
    if (position == 0) {
        remove_head(list);
    } else if (position == list->size - 1) {
        remove_tail(list);
    } else {
        node* dummy = list->head;
        for (int i = 1; i < position; i++) {
            dummy = dummy->next;
        }
        dummy->next->next->prev = dummy;
        node* tmp = dummy->next;
        dummy->next = dummy->next->next;
        free(tmp);
        list->size -= 1;
    }
}

void remove_by_value(linked_list* list, int value) {
    if (list == NULL) return;
    node* dummy = list->head;
    if (list->head->value == value) {
        remove_head(list);
        return;
    }
    while (dummy->next != NULL) {
        if (dummy->next->value == value) {
            if (dummy->next->next == NULL) {
                remove_tail(list);
                break;
            }
            dummy->next->next->prev = dummy;
            node* tmp = dummy->next;
            dummy->next = dummy->next->next;
            free(tmp);
            list->size -= 1;
        }
        dummy = dummy->next;
    }
}

void print_as_string_forward(linked_list* list) {
    if (list == NULL) return;
    node* dummy = list->head;
    printf("NULL -> ");
    while (dummy) {
        if (dummy->prev == NULL) {
            printf("(prev: NULL, curr: %d) -> ", dummy->value);
        } else
            printf("(prev: %d, curr: %d) -> ", dummy->prev ? dummy->prev->value : 0, dummy->value);
        dummy = dummy->next;
    }
    printf("NULL\n");
}

void print_as_string_backward(linked_list* list) {
    if (list == NULL) return;
    node* dummy = list->tail;
    printf("NULL -> ");
    while (dummy) {
        if (dummy->next == NULL) {
            printf("(prev: NULL, curr: %d) -> ", dummy->value);
        } else
            printf("(prev: %d, curr: %d) -> ", dummy->next ? dummy->next->value : 0, dummy->value);
        dummy = dummy->prev;
    }
    printf("NULL\n");
}

int get_size(linked_list* list) {
    if (list == NULL) return 0;
    return list->size;
}

bool is_empty(linked_list* list) {
    if (list == NULL) return 0;
    return list->size == 0;
}

int index_of(linked_list* list, int value) {
    if (list == NULL) return -1;
    node* dummy = list->head;
    int i = 0;
    while (dummy) {
        if (dummy->value == value) {
            return i;
        }
        i++;
        dummy = dummy->next;
    }
    return -1;
}

bool contains(linked_list* list, int value) {
    if (list == NULL) return false;
    node* dummy = list->head;
    while (dummy) {
        if (dummy->value == value) return true;
        dummy = dummy->next;
    }
    return false;
}

void update_by_index(linked_list* list, int position, int value) {
    if (list == NULL) return;
    if (position >= list->size) return;
    if (position < 0) return;
    node* dummy = list->head;
    for (int i = 0; i < position; i++) {
        dummy = dummy->next;
    }
    dummy->value = value;
}

linked_list* reverse_list(linked_list* list) {
    if (list == NULL) return list;
    node* curr = list->head;
    node* prev = NULL;
    while (curr) {
        node* tmp = curr->next;
        curr->next = prev;
        prev = curr;
        prev->prev = tmp;
        curr = tmp;
    }
    list->head = prev;
    node* dummy = list->head;
    while (dummy->next) {
        dummy = dummy->next;
    }
    list->tail = dummy;
    return list;
}

void free_list(linked_list* list) {
    if (list == NULL) return;
    linked_list* starting_pointer = list;
    node* dummy = list->head;
    while (dummy) {
        node* tmp = dummy;
        dummy = dummy->next;
        free(tmp);
    }
    free(starting_pointer);
} 