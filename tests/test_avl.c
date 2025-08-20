#include "../include/avl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(void) {
    printf("Testing AVL (Adelson-Velsky and Landis tree)...\n");
    printf("Testing create AVL...\n");
    avl* tree = create_tree();
    assert(tree != NULL);
    printf("OK.\n");

    printf("Testing insertion...\n");
    assert(insert_node(NULL, 123) == EXIT_FAILURE);
    assert(insert_node(tree, 5) == EXIT_SUCCESS);
    assert(insert_node(tree, 8) == EXIT_SUCCESS);
    assert(insert_node(tree, 11) == EXIT_SUCCESS);
    assert(insert_node(tree, 12) == EXIT_SUCCESS);
    assert(insert_node(tree, 17) == EXIT_SUCCESS);
    assert(insert_node(tree, 18) == EXIT_SUCCESS);
    assert(insert_node(tree, 20) == EXIT_SUCCESS);
    assert(insert_node(tree, 12) == EXIT_SUCCESS);
    assert(insert_node(tree, 30) == EXIT_SUCCESS);
    assert(insert_node(tree, 9) == EXIT_SUCCESS);
    print_avl(tree->root, 0, ' ');
    printf("OK.\n");

    printf("Testing searching...\n");
    avl_node* node;
    assert(search_node(NULL, 123, &node) == EXIT_FAILURE);
    assert(search_node(tree, 123, NULL) == EXIT_FAILURE);
    assert(search_node(tree, 30, &node) == EXIT_SUCCESS);
    assert(node->value == 30);
    printf("OK.\n");

    printf("Getting min of the tree...\n");
    int value;
    assert(min(NULL, &value) == EXIT_FAILURE);
    assert(min(tree, NULL) == EXIT_FAILURE);
    assert(min(tree, &value) == EXIT_SUCCESS);
    assert(value == 5);
    printf("OK.\n");

    printf("Getting max of the tree...\n");
    assert(max(NULL, &value) == EXIT_FAILURE);
    assert(max(tree, NULL) == EXIT_FAILURE);
    assert(max(tree, &value) == EXIT_SUCCESS);
    assert(value == 30);
    printf("OK.\n");

    printf("Getting height of the node...\n");
    print_avl(tree->root, 0, ' ');
    assert(get_node_height(tree->root) == 4);
    assert(get_node_height(tree->root->right) == 3);
    assert(get_node_height(NULL) == 0);
    printf("OK.\n");

    printf("In-order DFS...\n");
    print_avl(tree->root, 0, ' ');
    assert(in_order_dfs(NULL) == EXIT_FAILURE);
    assert(in_order_dfs(tree) == EXIT_SUCCESS);
    printf("OK.\n");

    printf("Pre-order DFS...\n");
    print_avl(tree->root, 0, ' ');
    assert(pre_order_dfs(NULL) == EXIT_FAILURE);
    assert(pre_order_dfs(tree) == EXIT_SUCCESS);
    printf("OK.\n");

    printf("Post-order DFS...\n");
    print_avl(tree->root, 0, ' ');
    assert(post_order_dfs(NULL) == EXIT_FAILURE);
    assert(post_order_dfs(tree) == EXIT_SUCCESS);
    printf("OK.\n");
    
    printf("BFS...\n");
    print_avl(tree->root, 0, ' ');
    assert(bfs(NULL) == EXIT_FAILURE);
    assert(bfs(tree) == EXIT_SUCCESS);
    printf("OK.\n");
    
    printf("Testing deleting...\n");
    assert(delete_node(NULL, 123) == EXIT_FAILURE);
    assert(delete_node(tree, 9) == EXIT_SUCCESS);
    assert(delete_node(tree, 18) == EXIT_SUCCESS);
    assert(delete_node(tree, 8) == EXIT_SUCCESS);
    assert(delete_node(tree, 5) == EXIT_SUCCESS);
    assert(delete_node(tree, 11) == EXIT_SUCCESS);
    printf("\n\n\n");
    print_avl(tree->root, 0, ' ');
    printf("OK.\n");

    printf("Freeing allocated memory...\n");
    assert(free_tree(NULL) == EXIT_FAILURE);
    assert(free_tree(tree) == EXIT_SUCCESS);
    printf("OK.\n");
}