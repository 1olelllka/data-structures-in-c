#include "../include/red_black.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

void test_simple_insertion(red_black_tree* tree) {
    printf("Simple insertions...\n");
    assert(insert(NULL, 0) == EXIT_FAILURE);

    assert(insert(tree, 10) == EXIT_SUCCESS);
    assert(insert(tree, 1) == EXIT_SUCCESS);
    assert(insert(tree, 20) == EXIT_SUCCESS);
    assert(insert(tree, 5) == EXIT_SUCCESS);
    assert(insert(tree, 15) == EXIT_SUCCESS);
    assert(insert(tree, 25) == EXIT_SUCCESS);

    assert(tree->root->color == BLACK);

    assert(tree->root->left->value == 1);
    assert(tree->root->right->value == 20);

    assert(tree->root->left->color == BLACK);
    assert(tree->root->right->color == BLACK);
    assert(tree->root->left->right->value == 5);
    assert(tree->root->left->right->color == RED);
    assert(tree->root->right->left->value == 15);
    assert(tree->root->right->left->color == RED);
    assert(tree->root->right->right->value == 25);
    assert(tree->root->right->right->color == RED);
    printf("Simple insertions: OK.\n");
}

void test_insertion_cases(red_black_tree* tree) {
    printf("Insertion cases...\n");
    assert(insert(tree, 13) == EXIT_SUCCESS); // left-left case
    assert(tree->root->right->value == 20);
    assert(tree->root->right->color == RED);
    assert(tree->root->right->right->color == BLACK);
    assert(tree->root->right->right->value == 25);
    assert(tree->root->right->left->color == BLACK);
    assert(tree->root->right->left->value == 15);
    assert(tree->root->right->left->left->color == RED);
    assert(tree->root->right->left->left->value == 13);
    printf("Left-left case: OK.\n");

    assert(insert(tree, 7) == EXIT_SUCCESS); // right-right case
    assert(tree->root->left->color == BLACK);
    assert(tree->root->left->value == 5);
    assert(tree->root->left->left->color == RED);
    assert(tree->root->left->left->value == 1);
    assert(tree->root->left->right->value == 7);
    assert(tree->root->left->right->color == RED);
    printf("Right-Right case: OK.\n");

    assert(insert(tree, 30) == EXIT_SUCCESS);

    assert(insert(tree, 27) == EXIT_SUCCESS); // right-left case
    assert(tree->root->right->right->color == BLACK);
    assert(tree->root->right->right->value == 27);
    assert(tree->root->right->right->left->color == RED);
    assert(tree->root->right->right->left->value == 25);
    assert(tree->root->right->right->right->color == RED);
    assert(tree->root->right->right->right->value == 30);
    assert(tree->number_of_nodes == 10);
    printf("Right-Left case: OK.\n");

    assert(insert(tree, 14) == EXIT_SUCCESS); // left-right case
    assert(tree->root->right->color == RED);
    assert(tree->root->right->value == 20);
    assert(tree->root->right->left->color == BLACK);
    assert(tree->root->right->left->value == 14);
    assert(tree->root->right->left->left->color == RED);
    assert(tree->root->right->left->left->value == 13);
    assert(tree->root->right->left->right->color == RED);
    assert(tree->root->right->left->right->value == 15);
    assert(tree->number_of_nodes == 11);
    printf("Left-Right case: OK.\n");
    printf("Insertion cases: OK.\n");
}

void test_insertion_duplicates(red_black_tree* tree) {
    printf("Inserting duplicates...");
    assert(insert(tree, 20) == EXIT_FAILURE);
    assert(tree->number_of_nodes == 11);
    printf("Inserting duplicates: OK.\n");
}

void test_cascade_tree() {
    // I create new tree to handle specific sequence of numbers, 
    // because it'll be harder to do so with default one
    printf("Inserting to check cascade tree...\n");
    red_black_tree* tree = create_red_black_tree();
    assert(tree != NULL);
    printf("Inserting values...\n");
    int values[] = {7, 3, 18, 10, 22, 8, 11, 26, 2, 6, 13};
    for (int i = 0; i < 11; i++) {
        assert(insert(tree, values[i]) == EXIT_SUCCESS);
    }
    printf("Inserting values: OK.\n");
    printf("Testing...\n");
    assert(tree->root->color == BLACK);
    assert(tree->root->value == 10);
    assert(tree->root->parent == NULL);
    // left subtree
    assert(tree->root->left->color == RED);
    assert(tree->root->left->value == 7);
    assert(tree->root->left->left->color == BLACK);
    assert(tree->root->left->left->value == 3);
    assert(tree->root->left->left->left->color == RED);
    assert(tree->root->left->left->left->value == 2);
    assert(tree->root->left->left->right->color == RED);
    assert(tree->root->left->left->right->value == 6);
    assert(tree->root->left->right->color == BLACK);
    assert(tree->root->left->right->value == 8);
    // right subtree
    assert(tree->root->right->color == RED);
    assert(tree->root->right->value == 18);
    assert(tree->root->right->left->color == BLACK);
    assert(tree->root->right->left->value == 11);
    assert(tree->root->right->left->right->color == RED);
    assert(tree->root->right->left->right->value == 13);
    assert(tree->root->right->right->color == BLACK);
    assert(tree->root->right->right->value == 22);
    assert(tree->root->right->right->right->color == RED);
    assert(tree->root->right->right->right->value == 26);
    assert(free_tree(tree) == EXIT_SUCCESS);
    printf("Cascade tree: OK.\n");
}

void test_simple_delete(red_black_tree* tree) {
    printf("Simple deletions...\n");
    assert(remove_node(NULL, 1) == EXIT_FAILURE);
    assert(remove_node(tree, 1) == EXIT_SUCCESS);
    assert(tree->root->left->left == NULL);
    assert(tree->root->left->color == BLACK);
    assert(tree->root->left->right->color == RED);
    assert(tree->root->left->right->value == 7);
    assert(remove_node(tree, 13) == EXIT_SUCCESS);
    assert(remove_node(tree, 14) == EXIT_SUCCESS);
    assert(tree->root->right->color == RED);
    assert(tree->root->right->left->color == BLACK);
    assert(tree->root->right->left->value == 15);
    assert(tree->root->right->left->right == NULL);
    assert(tree->root->right->left->left == NULL);
    printf("OK.\n");
}

void test_complex_delete() {
    red_black_tree* tree = create_red_black_tree();
    // Case 4
    int seq4[] = {10, -10, 30, 20, 38};
    for (int i = 0; i < 5; i++) {
        assert(insert(tree, seq4[i]) == EXIT_SUCCESS);
    }
    // Manually changing the colors to match future case
    tree->root->left->color = BLACK;
    tree->root->right->color = RED;
    tree->root->right->right->color = BLACK;
    tree->root->right->left->color = BLACK;
    assert(remove_node(tree, 20) == EXIT_SUCCESS);
    assert(tree->root->right->value == 30);
    assert(tree->root->right->color == BLACK);
    assert(tree->root->right->right->value == 38);
    assert(tree->root->right->right->color == RED);
    assert(tree->root->right->left == NULL);
    clean_tree(tree);

    /* Case: delete the root with two children */
    int seqRoot[] = {50, 25, 75, 10, 30, 60, 80};
    clean_tree(tree);
    for (int i = 0; i < 7; i++) {
        assert(insert(tree, seqRoot[i]) == EXIT_SUCCESS);
    }
    assert(remove_node(tree, 50) == EXIT_SUCCESS);  /* remove old root */
    /* New root must be black, still a BST */
    assert(tree->root != NULL);
    assert(tree->root->color == BLACK);
    assert(tree->root->value != 50);
    assert(tree->root->left->value == 25);
    assert(tree->root->left->color == BLACK);

    /* Case: delete a red leaf (simple) */
    int seqRedLeaf[] = {10, 5, 15};
    clean_tree(tree);
    for (int i = 0; i < 3; i++) {
        assert(insert(tree, seqRedLeaf[i]) == EXIT_SUCCESS);
    }
    /* Force 15 to be red */
    tree->root->right->color = RED;
    assert(remove_node(tree, 15) == EXIT_SUCCESS);
    assert(tree->root->value == 10);
    assert(tree->root->right == NULL);
    assert(tree->root->color == BLACK);

    /* Case: delete black node with one red child */
    int seqBlackWithRed[] = {10, 5, 15, 1};
    clean_tree(tree);
    for (int i = 0; i < 4; i++) {
        assert(insert(tree, seqBlackWithRed[i]) == EXIT_SUCCESS);
    }
    /* Force 1 to be red */
    tree->root->left->left->color = RED;
    assert(remove_node(tree, 5) == EXIT_SUCCESS);
    assert(tree->root->left->value == 1);
    assert(tree->root->left->color == BLACK);

    int seqEmpty[] = {10, 5, 15};
    clean_tree(tree);
    for (int i = 0; i < 3; i++) {
        assert(insert(tree, seqEmpty[i]) == EXIT_SUCCESS);
    }
    assert(remove_node(tree, 5) == EXIT_SUCCESS);
    assert(remove_node(tree, 15) == EXIT_SUCCESS);
    assert(remove_node(tree, 10) == EXIT_SUCCESS);
    assert(tree->root == NULL);
    assert(tree->number_of_nodes == 0);


    free_tree(tree);
}

int main(void) {
    printf("Testing Red-Black Tree...\n");
    printf("Creating Red-Black Tree...\n");
    red_black_tree* tree = create_red_black_tree();
    assert(tree != NULL);
    assert(tree->number_of_nodes == 0);
    printf("OK.\n");

    printf("Inserting with different scenarios into Red-Black Tree...\n");
    test_simple_insertion(tree);
    test_insertion_cases(tree);
    test_insertion_duplicates(tree);
    test_cascade_tree();
    printf("OK.\n");

    printf("Searching for the value in Red-Black Tree...\n");
    assert(search(NULL, 123, NULL) == EXIT_FAILURE);
    assert(search(tree, 123, NULL) == EXIT_FAILURE);
    node* res;
    assert(search(tree, 123, &res) == EXIT_FAILURE);
    assert(search(tree, 25, &res) == EXIT_SUCCESS);
    assert(res->value == 25);
    assert(res->color == RED);
    printf("OK.\n");

    printf("Removing nodes in Red-Black Tree...\n");
    test_simple_delete(tree);
    test_complex_delete();
    printf("OK.\n");

    printf("Cleaning Red-Black Tree...\n");
    assert(clean_tree(tree) == EXIT_SUCCESS);
    assert(clean_tree(NULL) == EXIT_FAILURE);
    printf("OK.\n");

    printf("Freeing allocated memory...\n");
    assert(free_tree(tree) == EXIT_SUCCESS);
    assert(free_tree(NULL) == EXIT_FAILURE);
    printf("OK.\n");
    return EXIT_SUCCESS;
}