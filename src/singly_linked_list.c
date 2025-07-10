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

linked_list* create_list() {
    linked_list* list = malloc(sizeof(linked_list));
    list->size = 0;
    list->head = NULL;
    return list;
}

void free_list(linked_list* list) {
    linked_list* start_pointer = list;
    // free every node
    while (list->head != NULL) {
        node* tmp = list->head;
        list->head = list->head->next;
        free(tmp);
    }
    // free the wrapper
    free(start_pointer);
}

void insert_head(linked_list* list, int value) {
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
    if (list->size == 0) return;
    node* tmp = list->head->next;
    free(list->head);
    list->head = tmp;
    list->size -= 1;
}

void remove_tail(linked_list* list) {
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
    node* dummy = list->head;
    while (dummy != NULL) {
        if (dummy->value == value) return true;
        dummy = dummy->next;
    }
    return false;
}

int index_of(linked_list* list, int value) {
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

void print_as_string(linked_list *list) {
    printf("list as string: ");
    node *elem = list->head;
    for (int i = 0; i < list->size; i++) {
        printf("%d ", elem->value);
        elem = elem->next;
    }
    printf("\n");
}

int main(void) {
    linked_list* list = create_list();
    insert_head(list, 10);
    print_as_string(list);
    insert_head(list, 11);
    print_as_string(list);
    insert_tail(list, 20);
    print_as_string(list);
    insert_position(list, 0, 55);
    print_as_string(list);
    // remove_by_value(list, 11);
    // print_as_string(list);
    // remove_head(list);
    // print_as_string(list);
    // remove_tail(list);
    // print_as_string(list);
    remove_by_index(list, 3);
    print_as_string(list);
    printf("Contains %d -> %d\n", 10, contains(list, 10));
    printf("Index of %d is %d\n", 10, index_of(list, 10));
    printf("Reversed:\n");
    // IMPLEMENT
    print_as_string(list);
    free_list(list);
    return EXIT_SUCCESS;
}