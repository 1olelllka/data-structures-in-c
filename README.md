# Data Structures in C
> Manual, memory-safe implementations of core data structures in C, with tests and Valgrind-clean guarantees.

### Implemented Structures
* Singly Linked List
* Doubly Linked List
* Stack (using linked list & arrays in C)
* Queue
* Binary Search Tree (BST)
* Adelson-Velsky and Landis Tree (AVL)
* Red-Black Tree
* Max Heap
* Hash Table (with both chaining and rehashing strategies)


## How to use it
```c
#include "<path_to_include>/<data_structure_name>.h"

// <your_code>
```
> Note: Before usage, check the API of data structure in headers file (.h extension)
### Example
```c
#include "./include/singly_linked_list.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    linked_list* ll = create_list();
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            insert_head(ll, i);
        } else {
            insert_tail(ll, i);
        }
    }
    print_as_string(ll);
    printf("Size: - %d nodes\n", get_size(ll));
    free_list(ll);
    return EXIT_SUCCESS;
}
```

## Tests
> Important Note: All of the CLI commands were performed on Ubuntu
* In order to run tests on any of implemented structures, type this (make sure, you have `make` installed)
```bash
make ./tests/test_<data_structure_name> # Compile
./tests/test_<data_structure_name>      # Run actual test
```
* Or if you want to run all tests
```bash
make all                           # Compile
./tests/test_<data_structure_name> # Run every test (type every path to executable, in future, I'll introduce the script that runs every test)
```
* Clean all exectutables and .o files
```bash
make clean
```

## Project Status
Simple implementations of main data structures are completed. Next, it is planned to make most of them generic and in perspective thread-safe. Development may pause during university semesters and resume during breaks.
