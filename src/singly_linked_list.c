#include "../include/singly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

linked_list* create_list() {
    linked_list* list = malloc(sizeof(linked_list));
    list->size = 0;
    list->head = NULL;
    return list;
}

void free_list(linked_list* list) {
    if (list == NULL) return;
    list->size = 0;
    linked_list* start_pointer = list;
    while (list->head != NULL) {
        node* tmp = list->head;
        list->head = list->head->next;
        free(tmp);
    }
    free(start_pointer);
}

void insert_head(linked_list* list, int value) {
    if (list == NULL) return;
    node* new_node = malloc(sizeof(node));
    new_node->value = value;
    if (list->size > 0) {
        node* tmp = list->head;
        list->head = new_node;
        list->head->next = tmp;
    } else {
        new_node->next = NULL;
        list->head = new_node;
    }
    list->size += 1;
}

void insert_tail(linked_list* list, int value) {
    if (list == NULL) return;
    node* new_node = malloc(sizeof(node));
    new_node->value = value;
    if (list->size == 0) {
        new_node->next = NULL;
        list->head = new_node;
    } else {
        node* dummy = list->head;
        while (dummy->next != NULL) {
            dummy = dummy->next;
        }
        new_node->next = NULL;
        dummy->next = new_node;
    }   
    list->size += 1;
}

void insert_position(linked_list* list, int position, int value) {
    if (list == NULL) return;
    if (position == 0) {
        insert_head(list, value);
        return;
    }
    if (list->size <= position) return;
    node* new_node = malloc(sizeof(node));
    new_node->value = value;
    if (list->size == 0) {
        new_node->next = NULL;
        list->head = new_node;
    } else {
        node* dummy = list->head;
        for (int i = 0; i < position - 1; i++) {
            dummy = dummy->next;
        }
        node* tmp = dummy->next;
        dummy->next = new_node;
        dummy->next->next = tmp;
    }
    list->size += 1;
}

void remove_head(linked_list* list) {
    if (list == NULL) return;
    if (list->size == 0) return;
    node* tmp = list->head->next;
    free(list->head);
    list->head = tmp;
    list->size -= 1;
}

void remove_tail(linked_list* list) {
    if (list == NULL) return;
    if (list->size == 0) return;
    if (list->size == 1) {
        free(list->head);
        list->head = NULL;
    } else {
        node* dummy = list->head;
        while (dummy->next->next != NULL) {
            dummy = dummy->next;
        }
        node* elem = dummy->next;
        dummy->next = dummy->next->next;
        free(elem);
    }
    list->size -= 1;
}

void remove_by_index(linked_list* list, int index) {
    if (list == NULL) return;
    if (list->size == 0) return;
    if (list->size <= index) return;
    if (index == 0) {
        remove_head(list);
        return;
    }
    node* dummy = list->head;
    for (int i = 0; i < index - 1; i++) {
        dummy = dummy->next;
    }
    node* tmp = dummy->next;
    dummy->next = dummy->next->next;
    free(tmp);
    list->size -= 1;
}

void remove_by_value(linked_list* list, int value) {
    if (list == NULL) return;
    if (list->size == 0) return;
    if (list->size == 1) {
        if (list->head->value == value) {
            node* tmp = list->head;
            list->head = NULL;
            free(tmp);
            list->size -= 1;
        }
        return;
    }
    if (list->head->value == value) {
        node* tmp = list->head;
        list->head = list->head->next;
        free(tmp);
        list->size -= 1;
        return;
    }
    node* dummy = list->head;
    while (dummy->next != NULL && dummy->next->value != value) {
        dummy = dummy->next;
    }
    if (dummy->next != NULL && dummy->next->value == value) {
        node* tmp = dummy->next;
        dummy->next = dummy->next->next;
        free(tmp);
        list->size -= 1;
    }
    return;
}

bool contains(linked_list* list, int value) {
    if (list == NULL) return false;
    node* dummy = list->head;
    while (dummy != NULL) {
        if (dummy->value == value) return true;
        dummy = dummy->next;
    }
    return false;
}

int index_of(linked_list* list, int value) {
    if (list == NULL) return -1;
    if (list->size == 0) return -1;
    node* dummy = list->head;
    int i = 0;
    while (dummy != NULL) {
        if (dummy->value == value) {
            return i;
        }
        i++;
        dummy = dummy->next;
    }
    return -1;
}

int is_empty(linked_list* list) {
    if (list == NULL) return 1;
    return list->size == 0;
}

int get_size(linked_list* list) {
    if (list == NULL) return 0;
    return list->size;
}

void update_by_index(linked_list* list, int index, int value) {
    if (list == NULL) return;
    if (list->size <= 0) return;
    if (list->size <= index) return;
    node* dummy = list->head;
    int i = 0;
    while (dummy != NULL) {
        if (i == index) {
            dummy->value = value;
            break;
        }
        i++;
        dummy = dummy->next;
    }
}

linked_list* reverse_list(linked_list* list) {
    if (list == NULL) return NULL;
    if (list->size == 0) return list;
    node* curr = list->head;
    node* prev = NULL;
    while (curr) {
        node* tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }
    list->head = prev;
    return list;
}

void print_as_string(linked_list *list) {
    if (list == NULL) return;
    printf("List: ");
    node *elem = list->head;
    for (int i = 0; i < list->size; i++) {
        printf("%d -> ", elem->value);
        elem = elem->next;
    }
    printf("NULL\n");
}