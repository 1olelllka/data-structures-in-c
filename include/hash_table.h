#ifndef _HASH_TABLE

#define _HASH_TABLE
#include <stdlib.h>

struct node {
    char* key;
    char* value;
    struct node* next;
};

typedef struct _hash_table {
    size_t capacity;
    size_t size;
    struct node** data;
} hash_table;


hash_table* create_hash_table(size_t capacity);

size_t hash(hash_table* table, char* key);

int insert(hash_table* table, char* key, char* value);

int pop(hash_table* table, char* key);

void print_hash_table(const hash_table* table);

char* search(hash_table* table, char* key);

size_t get_size(hash_table* table);

size_t get_capacity(hash_table* table);

int free_hash_table(hash_table* table);

#endif