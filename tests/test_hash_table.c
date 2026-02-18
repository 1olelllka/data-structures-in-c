#include "../include/hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main(void) {
    printf("Testing create a hash table...\n");
    hash_table* table = create_hash_table(3);
    assert(table != NULL);
    assert(get_size(table) == 0);
    assert(get_capacity(table) == 3);
    print_hash_table(table);
    printf("OK.\n");

    printf("Testing insert into a hash table...\n");
    assert(insert(table, "ab", "1234") == EXIT_SUCCESS);
    assert(get_size(table) == 1);
    assert(get_capacity(table) == 3);
    assert(search(table, "ab") != NULL);
    print_hash_table(table);
    printf("OK.\n");
    printf("Testing chaining strategy...\n");
    assert(insert(table, "ba", "4321") == EXIT_SUCCESS);
    assert(get_size(table) == 2);
    assert(get_capacity(table) == 3);
    print_hash_table(table);
    assert(search(table, "ba") != NULL);
    printf("OK.\n");
    printf("Testing rehashing strategy...\n");
    assert(insert(table, "abc", "10-11-12") == EXIT_SUCCESS);
    assert(get_size(table) == 3);
    assert(get_capacity(table) == 6);
    assert(search(table, "abc") != NULL);
    assert(search(table, "ba") != NULL);
    assert(search(table, "ab") != NULL);
    print_hash_table(table);
    printf("OK.\n");
    printf("Testing inserting duplicates...\n");
    assert(insert(table, "ba", "duplicate") == EXIT_SUCCESS);
    assert(strcmp(search(table, "ba"), "4321") != 0);
    assert(get_size(table) == 3);
    print_hash_table(table);
    printf("OK.\n");

    printf("Testing search inside of a hash table...\n");
    assert(search(table, "incorrect_key") == NULL);
    assert(search(table, "ba") != NULL);
    printf("OK.\n");

    printf("Testing popping from the hash table...\n");
    assert(pop(table, "incorrect_key") == EXIT_SUCCESS);
    assert(get_size(table) == 3);
    assert(pop(table, "ba") == EXIT_SUCCESS);
    assert(get_size(table) == 2);
    print_hash_table(table);
    printf("OK.\n");

    printf("Testing free allocated hash table...\n");
    assert(free_hash_table(table) == EXIT_SUCCESS);
    printf("OK.\n");

    return EXIT_SUCCESS;
}