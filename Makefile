CC = gcc
CFLAGS = -Wall -Wextra -O2

.PHONY: all, clean

all: ./tests/test_singly_linked_list ./tests/test_doubly_linked_list ./tests/test_dynamic_stack

./tests/test_singly_linked_list: ./src/singly_linked_list.o ./tests/test_singly_linked_list.o

./tests/test_doubly_linked_list: ./src/doubly_linked_list.o ./tests/test_doubly_linked_list.o

./tests/test_dynamic_stack: ./src/dynamic_stack.o ./tests/test_dynamic_stack.o

clean:
	rm ./src/*.o ./tests/*.o ./tests/test_singly_linked_list ./tests/test_doubly_linked_list ./tests/test_dynamic_stack