#include "../include/avl.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

avl* create_tree() {
    avl* tree = malloc(sizeof(avl));
    if (tree == NULL) {
        perror("malloc() error");
        return NULL;
    }
    tree->number_of_nodes = 0;
    tree->root = NULL;
    return tree;
}

int get_node_height(avl_node* node) {
    if (node == NULL) return 0;
    return node->height;
}

int get_min(avl_node* node) {
    if (node == NULL) return INT_MIN;
    avl_node* dummy = node;
    while (dummy->left) {
        dummy = dummy->left;
    }
    return dummy->value;
}

int min(avl* tree, int* value) {
    if (tree == NULL) return EXIT_FAILURE;
    if (tree->root == NULL) return EXIT_FAILURE;
    if (value == NULL) return EXIT_FAILURE;
    *value = get_min(tree->root);
    return EXIT_SUCCESS;
}

int get_max(avl_node* node) {
    if (node == NULL) return INT_MAX;
    avl_node* dummy = node;
    while (dummy->right) {
        dummy = dummy->right;
    }
    return dummy->value;
}

int max(avl* tree, int* value) {
    if (tree == NULL) return EXIT_FAILURE;
    if (tree->root == NULL) return EXIT_FAILURE;
    if (value == NULL) return EXIT_FAILURE;
    *value = get_max(tree->root);
    return EXIT_SUCCESS;
}

avl_node* ll_case(avl_node* root) {
    avl_node* new_root = root->left;
    avl_node* right_children = new_root->right;
    new_root->right = root;
    root->left = right_children;
    root->height = get_node_height(root->left) > get_node_height(root->right) ?
        1 + get_node_height(root->left) : 1 + get_node_height(root->right);
    new_root->height = get_node_height(new_root->left) > get_node_height(new_root->right) ?
        1 + get_node_height(new_root->left) : 1 + get_node_height(new_root->right);
    return new_root;
}

avl_node* rr_case(avl_node* root) {
    avl_node* new_root = root->right;
    avl_node* left_children = new_root->left;
    new_root->left = root;
    root->right = left_children;
    root->height = get_node_height(root->left) > get_node_height(root->right) ?
        1 + get_node_height(root->left) : 1 + get_node_height(root->right);
    new_root->height = get_node_height(new_root->left) > get_node_height(new_root->right) ?
        1 + get_node_height(new_root->left) : 1 + get_node_height(new_root->right);
    return new_root;
}

avl_node* lr_case(avl_node* root) {
    return ll_case(rr_case(root->left));
}

avl_node* rl_case(avl_node* root) {
    return rr_case(ll_case(root->right));
}

avl_node* balance_tree(avl_node* root) {
    if (root == NULL) return NULL;
    int left_subtree = get_node_height(root->left);
    int right_subtree = get_node_height(root->right);
    if (left_subtree - right_subtree > 1) {
        left_subtree = get_node_height(root->left->left);
        right_subtree = get_node_height(root->left->right);
        if (left_subtree - right_subtree < 0) {
            return lr_case(root);
        } else {
            return ll_case(root);
        }
    } else if (left_subtree - right_subtree < -1) {
        left_subtree = get_node_height(root->right->left);
        right_subtree = get_node_height(root->right->right);
        if (right_subtree - left_subtree < 0) {
            return rl_case(root);
        } else {
            return rr_case(root);
        }
    }
    return root;
}

avl_node* insertion_helper(avl_node* root, int value, int* number_of_nodes) {
    if (root == NULL) {
        avl_node* new_node = malloc(sizeof(avl_node));
        new_node->value = value;
        new_node->height = 1;
        new_node->right = NULL;
        new_node->left = NULL;
        *number_of_nodes += 1;
        return new_node;
    }
    if (root->value > value) {
        root->left = insertion_helper(root->left, value, number_of_nodes);
    } else if (root->value < value) {
        root->right = insertion_helper(root->right, value, number_of_nodes);
    } else {
        return root;
    }
    int left_subtree = get_node_height(root->left);
    int right_subtree = get_node_height(root->right);
    root->height = left_subtree > right_subtree ? left_subtree + 1 : right_subtree + 1;
    return balance_tree(root);
}

int insert_node(avl* tree, int value) {
    if (tree == NULL) return EXIT_FAILURE;
    tree->root = insertion_helper(tree->root, value, &tree->number_of_nodes);
    return EXIT_SUCCESS;
}

int search_node(avl* tree, int value, avl_node** result) {
    if (tree == NULL) return EXIT_FAILURE;
    if (result == NULL) return EXIT_FAILURE;
    avl_node* dummy = tree->root;
    while (dummy) {
        if (dummy->value > value) {
            dummy = dummy->left;
        } else if (dummy->value < value) {
            dummy = dummy->right;
        } else {
            *result = dummy;
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

avl_node* delete_helper(avl_node* root, int value, int* number_of_nodes) {
    if (root == NULL) {
        return NULL;
    }
    if (root->value > value)  {
        root->left = delete_helper(root->left, value, number_of_nodes);
    } else if (root->value < value) {
        root->right = delete_helper(root->right, value, number_of_nodes);
    } else {
        if (!root->right) {
            avl_node* tmp = root->left;
            free(root);
            *number_of_nodes -= 1;
            return tmp;
        }
        if (!root->left) {
            avl_node* tmp = root->right;
            free(root);
            *number_of_nodes -= 1;
            return tmp;
        }
        int min = get_min(root->right);
        root->value = min;
        root->right = delete_helper(root->right, min, number_of_nodes);
    }
    int left_subtree = get_node_height(root->left);
    int right_subtree = get_node_height(root->right);
    root->height = left_subtree > right_subtree ? left_subtree + 1 : right_subtree + 1;
    return balance_tree(root);
}

int delete_node(avl* tree, int value) {
    if (tree == NULL) return EXIT_FAILURE;
    tree->root = delete_helper(tree->root, value, &tree->number_of_nodes);
    return EXIT_SUCCESS;
}

void clear_tree(avl_node* root) {
    if (root == NULL) return;
    clear_tree(root->left);
    clear_tree(root->right);
    free(root);
}

int free_tree(avl* tree) {
    if (tree == NULL) return EXIT_FAILURE;
    if (tree->root) {
        clear_tree(tree->root);
    }
    free(tree);
    return EXIT_SUCCESS;
}

void print_avl(avl_node* root, int depth, char prefix) {
    if (root == NULL)
        return;
    print_avl(root->right, depth + 1, '/');
    for (int i = 0; i < depth; i++)
        printf("    ");
    if (depth > 0)
        printf("%c── ", prefix);
    printf("%d\n", root->value);

    print_avl(root->left, depth + 1, '\\');
}

void in_order_helper(avl_node* root) {
    if (root == NULL) return;
    in_order_helper(root->left);
    printf("%d ", root->value);
    in_order_helper(root->right);
}

int in_order_dfs(avl* tree) {
    if (tree == NULL) return EXIT_FAILURE;
    in_order_helper(tree->root);
    printf("\n");
    return EXIT_SUCCESS;
}

void pre_order_helper(avl_node* root) {
    if (root == NULL) return;
    printf("%d ", root->value);
    pre_order_helper(root->left);
    pre_order_helper(root->right);
}

int pre_order_dfs(avl* tree) {
    if (tree == NULL) return EXIT_FAILURE;
    pre_order_helper(tree->root);
    printf("\n");
    return EXIT_SUCCESS;
}

void post_order_helper(avl_node* root) {
    if (root == NULL) return;
    post_order_helper(root->left);
    post_order_helper(root->right);
    printf("%d ", root->value);
}

int post_order_dfs(avl* tree) {
    if (tree == NULL) return EXIT_FAILURE;
    post_order_helper(tree->root);
    printf("\n");
    return EXIT_SUCCESS;
}

int bfs(avl* tree) {
    if (tree == NULL) return EXIT_FAILURE;
    if (tree->number_of_nodes == 0) return EXIT_SUCCESS;
    avl_node** queue = malloc(sizeof(avl_node*) * tree->number_of_nodes);
    if (queue == NULL) {
        perror("malloc() error");
        return EXIT_FAILURE;
    }
    int front = 0;
    int rear = 0;
    queue[rear++] = tree->root;
    while (front < rear) {
        avl_node* node = queue[front++];
        printf("%d ", node->value);
        if (node->left) {
            queue[rear++] = node->left;
        }
        if (node->right) {
            queue[rear++] = node->right;
        }
    }
    printf("\n");
    free(queue);
    return EXIT_SUCCESS;
}