CC = gcc
CFLAGS = -Wall -Wextra -O2

.PHONY: all, clean

all: ./tests/test_singly_linked_list ./tests/test_doubly_linked_list ./tests/test_linked_list_stack ./tests/test_array_stack ./tests/test_linked_list_queue ./tests/test_bst ./tests/test_avl ./tests/test_red_black

./tests/test_singly_linked_list: ./src/singly_linked_list.o ./tests/test_singly_linked_list.o

./tests/test_doubly_linked_list: ./src/doubly_linked_list.o ./tests/test_doubly_linked_list.o

./tests/test_linked_list_stack: ./src/linked_list_stack.o ./tests/test_linked_list_stack.o

./tests/test_array_stack: ./src/array_stack.o ./tests/test_array_stack.o

./tests/test_linked_list_queue: ./src/linked_list_queue.o ./tests/test_linked_list_queue.o

./tests/test_bst: ./src/bst.o ./tests/test_bst.o

./tests/test_red_black: ./src/red_black.o ./tests/test_red_black.o

./tests/test_avl: ./src/avl.o ./tests/test_avl.o

clean:
	rm ./src/*.o ./tests/*.o ./tests/test_singly_linked_list ./tests/test_doubly_linked_list ./tests/test_linked_list_stack ./tests/test_array_stack ./tests/test_linked_list_queue ./tests/test_bst ./tests/test_avl ./tests/test_red_black