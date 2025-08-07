#include "../include/bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void) {

    printf("Creating BST - Binary Search Tree...\n");
    bst* tree = create_bst();
    assert(tree != NULL);
    printf("OK.\n");

    printf("Inserting values inside of BST...\n");
    assert(insert_node(NULL, 1) == EXIT_FAILURE);
    assert(insert_node(tree, 8) == EXIT_SUCCESS);
    assert(insert_node(tree, 3) == EXIT_SUCCESS);
    assert(insert_node(tree, 10) == EXIT_SUCCESS);
    assert(insert_node(tree, 1) == EXIT_SUCCESS);
    assert(insert_node(tree, 9) == EXIT_SUCCESS);
    assert(insert_node(tree, 2) == EXIT_SUCCESS);
    assert(insert_node(tree, 6) == EXIT_SUCCESS);
    assert(insert_node(tree, 4) == EXIT_SUCCESS);
    assert(insert_node(tree, 7) == EXIT_SUCCESS);
    assert(insert_node(tree, 14) == EXIT_SUCCESS);
    assert(insert_node(tree, 13) == EXIT_SUCCESS);
    assert(insert_node(tree, 12) == EXIT_SUCCESS);
    print_tree(tree->root, 0, ' ');
    printf("OK.\n");

    printf("Removing values from the BST...\n");
    assert(remove_node(NULL, 13) == EXIT_FAILURE);
    printf("Case 1: 0 or 1 child...\n");
    assert(remove_node(tree, 13) == EXIT_SUCCESS);
    print_tree(tree->root, 0, ' ');
    printf("OK.\n");
    printf("Case 2: 2 children...\n");
    assert(remove_node(tree, 8) == EXIT_SUCCESS);
    print_tree(tree->root, 0, ' ');
    printf("OK.\n");

    printf("Searching for specific value...\n");
    tree_node* searched_item;
    assert(search_node(NULL, 123, &searched_item) == EXIT_FAILURE);
    assert(search_node(tree, 123, NULL) == EXIT_FAILURE);
    assert(search_node(tree, 9, &searched_item) == EXIT_SUCCESS);
    assert(searched_item != NULL);
    assert(searched_item->right->value == 10);
    assert(searched_item->left->value == 3);
    assert(search_node(tree, 1234, &searched_item) == EXIT_FAILURE);
    print_tree(searched_item, 0, ' ');
    printf("OK.\n");

    printf("DFS...\n");
    assert(in_order_dfs(NULL) == EXIT_FAILURE);
    assert(in_order_dfs(tree) == EXIT_SUCCESS);
    assert(preorder_dfs(NULL) == EXIT_FAILURE);
    assert(preorder_dfs(tree) == EXIT_SUCCESS);
    assert(postorder_dfs(NULL) == EXIT_FAILURE);
    assert(postorder_dfs(tree) == EXIT_SUCCESS);
    printf("OK.\n");

    printf("BFS...\n");
    assert(bfs(NULL) == EXIT_FAILURE);
    assert(bfs(tree) == EXIT_SUCCESS);
    printf("OK.\n");

    printf("Testing to get the minimum value...\n");
    int value;
    assert(min(NULL, &value) == EXIT_FAILURE);
    assert(min(tree, NULL) == EXIT_FAILURE);
    assert(min(tree, &value) == EXIT_SUCCESS);
    assert(value == 1);
    printf("OK.\n");

    printf("Testing to get the maximum value...\n");
    assert(max(NULL, &value) == EXIT_FAILURE);
    assert(max(tree, NULL) == EXIT_FAILURE);
    assert(max(tree, &value) == EXIT_SUCCESS);
    assert(value == 14);
    printf("OK.\n");

    printf("Getting size of the tree...\n");
    assert(get_size(NULL, &value) == EXIT_FAILURE);
    assert(get_size(tree, NULL) == EXIT_FAILURE);
    assert(get_size(tree, &value) == EXIT_SUCCESS);
    assert(value == 10);
    printf("OK.\n");

    printf("Getting height of the tree...\n");
    assert(get_height(NULL, &value) == EXIT_FAILURE);
    assert(get_height(tree, NULL) == EXIT_FAILURE);
    assert(get_height(tree, &value) == EXIT_SUCCESS);
    printf("%d\n", value);
    assert(value == 4);
    printf("OK.\n");

    printf("Getting values of specific range...\n");
    assert(bst_range(NULL, 1, 1) == EXIT_FAILURE);
    assert(bst_range(tree, 4, 9) == EXIT_SUCCESS);
    printf("OK.\n");

    printf("Clearing BST...\n");
    assert(clear_bst(NULL) == EXIT_FAILURE);
    clear_bst(tree);
    assert(get_size(tree, &value) == EXIT_SUCCESS);
    assert(value == 0);
    printf("...and checking if reusable...\n");
    assert(insert_node(tree, 1) == EXIT_SUCCESS);
    assert(insert_node(tree, 2) == EXIT_SUCCESS);
    assert(insert_node(tree, 10) == EXIT_SUCCESS);
    assert(insert_node(tree, 6) == EXIT_SUCCESS);
    assert(remove_node(tree, 2) == EXIT_SUCCESS);
    assert(get_size(tree, &value) == EXIT_SUCCESS);
    assert(value == 3);
    printf("OK.\n");

    printf("Freeing BST...\n");
    assert(free_bst(NULL) == EXIT_FAILURE);
    assert(free_bst(tree) == EXIT_SUCCESS);
    printf("OK.\n");

    return EXIT_SUCCESS;
}