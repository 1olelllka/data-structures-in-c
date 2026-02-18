#include "../include/hash_table.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LOAD_FACTOR_THRESHOLD 0.75


hash_table* create_hash_table(size_t capacity) {
    if (capacity == 0) return NULL;
    hash_table* table = malloc(sizeof(hash_table));
    if (table == NULL) {
        perror("Error allocating memory for hash table");
        return NULL;
    }
    table->capacity = capacity;
    table->size = 0;
    table->data = calloc(table->capacity, sizeof(struct node*));
    if (table->data == NULL) {
        perror("Error allcating memory for hash table's data");
        free(table);
        return NULL;
    }
    return table;
}

size_t hash(hash_table* table, char* key) {
    size_t idx = 0;
    size_t i = 0;
    while (key[i] != '\0') {
        idx += key[i];
        i++;
    }
    return idx % table->capacity;
}

size_t get_size(hash_table* table) {
    if (table == NULL || table->data == NULL) return 0;
    return table->size;
}

size_t get_capacity(hash_table* table) {
    if (table == NULL || table->data == NULL) return 0;
    return table->capacity;
}

int rehash(hash_table* table) {
    struct node** new_data = calloc(table->capacity * 2, sizeof(struct node*));
    if (new_data == NULL) {
        perror("Error reallocating memory for hash table's data");
        return EXIT_FAILURE;
    }
    size_t old_capacity = table->capacity;
    table->capacity *= 2;
    for (size_t i = 0; i < old_capacity; i++) {
        struct node* nd = table->data[i];
        while (nd != NULL) {
            size_t new_idx = hash(table, nd->key);
            struct node* next = nd->next;
            nd->next = new_data[new_idx];
            new_data[new_idx] = nd;
            nd = next;
        }
    }
    free(table->data);
    table->data = new_data;
    return EXIT_SUCCESS;
}

int insert(hash_table* table, char* key, char* value) {
    if (table == NULL || table->data == NULL) return EXIT_FAILURE;
    if (key == NULL || value == NULL) return EXIT_FAILURE;
    size_t hash_idx = hash(table, key);
    struct node* curr = table->data[hash_idx];
    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            char* old_val = curr->value;
            curr->value = strdup(value);
            if (curr->value == NULL) {
                perror("Error allocating the memory for value");
                curr->value = old_val;
                return EXIT_FAILURE;
            }
            free(old_val);
            return EXIT_SUCCESS;
        }
        curr = curr->next;
    }

    if ((float)(table->size + 1) / table->capacity > LOAD_FACTOR_THRESHOLD) {
        if (rehash(table) != EXIT_SUCCESS) return EXIT_FAILURE;
        hash_idx = hash(table, key);
    }

    struct node* new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        perror("Error while allocating memory for the new node");
        return EXIT_FAILURE;
    }
    new_node->next = NULL;
    new_node->key = strdup(key);
    if (new_node->key == NULL) {
        perror("Error duplicating the key");
        free(new_node);
        return EXIT_FAILURE;
    }
    new_node->value = strdup(value);
    if (new_node->value == NULL) {
        perror("Error duplicating the value");
        free(new_node->key);
        free(new_node);
        return EXIT_FAILURE;
    }
    new_node->next = table->data[hash_idx];
    table->data[hash_idx] = new_node;
    table->size += 1;
    return EXIT_SUCCESS;
}

char* search(hash_table* table, char* key) {
    if (table == NULL || table->data == NULL) return NULL;
    if (table->size == 0) return NULL;
    if (key == NULL) return NULL;
    size_t idx = hash(table, key);
    struct node* elem = table->data[idx];
    while (elem != NULL) {
        if (strcmp(elem->key, key) == 0) {
            return elem->value;
        }
        elem = elem->next;
    }
    return NULL;
}

int pop(hash_table* table, char* key) {
    if (table == NULL || table->data == NULL || table->size == 0) return EXIT_FAILURE;
    if (key == NULL) return EXIT_FAILURE;
    size_t hash_idx = hash(table, key);
    struct node* elem = table->data[hash_idx];
    if (elem == NULL) {
        return EXIT_SUCCESS;
    }
    struct node* prev = NULL;
    while (elem != NULL) {
        if (strcmp(elem->key, key) == 0) {
            if (prev == NULL) {
                table->data[hash_idx] = elem->next;
            } else {
                prev->next = elem->next;
            }
            free(elem->key);
            free(elem->value);
            free(elem);
            table->size -= 1;
            return EXIT_SUCCESS;
        }
        prev = elem;
        elem = elem->next;
    }
    return EXIT_SUCCESS;
}

void print_hash_table(const hash_table* table) {
    if (table == NULL || table->data == NULL) {
        printf("Hash table is NULL.\n");
        return;
    }

    printf("Hash Table\n");
    printf("Capacity: %zu\n", table->capacity);
    printf("Size: %zu\n", table->size);
    printf("-----------------------------\n");

    for (size_t i = 0; i < table->capacity; i++) {
        printf("[%zu]: ", i);

        struct node* curr = table->data[i];
        if (curr == NULL) {
            printf("NULL");
        }

        while (curr != NULL) {
            printf("(\"%s\" : \"%s\")", curr->key, curr->value);
            if (curr->next != NULL) {
                printf(" -> ");
            }
            curr = curr->next;
        }

        printf("\n");
    }

    printf("-----------------------------\n");
}

int free_hash_table(hash_table* table) {
    if (table == NULL) return EXIT_FAILURE;
    if (table->data == NULL) return EXIT_FAILURE;
    for (size_t i = 0; i < table->capacity; i++) {
        struct node* data = table->data[i];
        while (data != NULL) {
            struct node* tmp = data->next;
            free(data->key);
            free(data->value);
            free(data);
            data = tmp;
        }
    }
    free(table->data);
    free(table);
    return EXIT_SUCCESS;
}