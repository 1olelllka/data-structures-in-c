#include "../include/bst.h"
#include <stdlib.h>
#include <stdio.h>

bst* create_bst() {
    bst* tree = malloc(sizeof(bst));
    if (tree == NULL) {
        perror("ERROR malloc()");
        return NULL;
    }
    tree->root = NULL;
    tree->number_of_nodes = 0;
    return tree;
}


tree_node* insert_helper(tree_node* root, tree_node* n, int* number_of_nodes) {
    if (root == NULL) {
        *number_of_nodes += 1;
        return n;
    }
    if (root->value > n->value) {
        root->left = insert_helper(root->left, n, number_of_nodes);
    } else if (root->value < n->value) {
        root->right = insert_helper(root->right, n, number_of_nodes);
    } else {
        printf("Duplicate tree_node. Aborting...\n");
    }
    return root;
}

int insert_node(bst* tree, int value) {
    if (tree == NULL) return EXIT_FAILURE;
    tree_node* new_tree_node = malloc(sizeof(tree_node));
    if (new_tree_node == NULL) {
        perror("ERROR malloc()");
        return EXIT_FAILURE;
    }
    new_tree_node->value = value;
    new_tree_node->left = NULL;
    new_tree_node->right = NULL;
    tree->root = insert_helper(tree->root, new_tree_node, &tree->number_of_nodes);
    return EXIT_SUCCESS;
}

tree_node* min_value_tree_node(tree_node* root) {
    if (!root) return NULL;
    tree_node* dummy = root;
    while (dummy->left) {
        dummy = dummy->left;
    }
    return dummy;
}

tree_node* remove_helper(tree_node* root, int value, int* number_of_nodes) {
    if (!root) return NULL;
    if (root->value < value) {
        root->right = remove_helper(root->right, value, number_of_nodes);
    } else if (root->value > value) {
        root->left = remove_helper(root->left, value, number_of_nodes);
    } else {
        if (!root->left) {
            tree_node* tmp = root->right;
            *number_of_nodes -= 1;
            free(root);
            return tmp;
        } else if (!root->right) {
            tree_node* tmp = root->left;
            *number_of_nodes -= 1;
            free(root);
            return tmp;
        } else {
            tree_node* min_tree_node = min_value_tree_node(root->right);
            root->value = min_tree_node->value;
            root->right = remove_helper(root->right, min_tree_node->value, number_of_nodes);
        }
    }
    return root;
}

int remove_node(bst* tree, int value) {
    if (tree == NULL) return EXIT_FAILURE;
    tree_node* new_root = remove_helper(tree->root, value, &tree->number_of_nodes);
    if (new_root) tree->root = new_root;
    else return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int search_node(bst* tree, int value, tree_node** node) {
    if (tree == NULL || node == NULL) return EXIT_FAILURE;
    tree_node* dummy = tree->root;
    while (dummy) {
        if (dummy->value > value) {
            dummy = dummy->left;
        } else if (dummy->value < value) {
            dummy = dummy->right;
        } else {
            *node = dummy;
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

int get_height_helper(tree_node* root) {
    if (root == NULL) return 0;
    int res1 = get_height_helper(root->left) + 1;
    int res2 = get_height_helper(root->right) + 1;
    return res1 > res2 ? res1 : res2;
}

int get_height(bst* tree, int* value) {
    if (tree == NULL || value == NULL) return EXIT_FAILURE;
    *value = get_height_helper(tree->root);
    return EXIT_SUCCESS;
}

void in_order_dfs_helper(tree_node* root) {
    if (!root) return;
    in_order_dfs_helper(root->left);
    printf("%d ", root->value);
    in_order_dfs_helper(root->right);
}

int in_order_dfs(bst* tree) {
    if (!tree) {
        printf("Please provide the valid tree.\n");
        return EXIT_FAILURE;
    }
    printf("In-order Depth-First-Search Traversal:\n");
    in_order_dfs_helper(tree->root);
    printf("\n");
    return EXIT_SUCCESS;
}

void preorder_dfs_helper(tree_node* root) {
    if (root == NULL) return;
    printf("%d ", root->value);
    preorder_dfs_helper(root->left);
    preorder_dfs_helper(root->right);
}

int preorder_dfs(bst* tree) {
    if (!tree) {
        printf("Please provide the valid tree.\n");
        return EXIT_FAILURE;
    }
    printf("Pre-Order Depth-First-Search Traversal:\n");
    preorder_dfs_helper(tree->root);
    printf("\n");
    return EXIT_SUCCESS;
}

void postorder_dfs_helper(tree_node* root) {
    if (root == NULL) return;
    postorder_dfs_helper(root->left);
    postorder_dfs_helper(root->right);
    printf("%d ", root->value);
}

int postorder_dfs(bst* tree) {
    if (!tree) {
        printf("Please provide the valid tree.\n");
        return EXIT_FAILURE;
    }
    printf("Post-Order Depth-First-Search Traversal:\n");
    postorder_dfs_helper(tree->root);
    printf("\n");
    return EXIT_SUCCESS;
}

int bfs(bst* tree) {
    if (!tree) {
        printf("Please provide the valid tree.\n");
        return EXIT_FAILURE;
    }
    if (!tree->root) return EXIT_FAILURE;
    tree_node* dummy = tree->root;
    tree_node** queue = calloc(tree->number_of_nodes, sizeof(tree_node*));
    if (!queue) {
        perror("calloc() error");
        return EXIT_FAILURE;
    }
    int front = 0;
    int rear = 0;
    queue[rear++] = dummy;
    while (front < rear) {
        tree_node* node = queue[front++];
        printf("%d ", node->value);
        if (node->left) {
            queue[rear++] = node->left;
        }
        if (node->right) {
            queue[rear++] = node->right;
        }
    }
    free(queue);
    printf("\n");
    return EXIT_SUCCESS;
}

int min(bst* tree, int* value) {
    if (tree == NULL || value == NULL) {
        return EXIT_FAILURE;
    }
    if (tree->root == NULL) {
        return EXIT_FAILURE;
    }
    tree_node* dummy = tree->root;
    while (dummy->left) {
        dummy = dummy->left;
    }
    *value = dummy->value;
    return EXIT_SUCCESS;
}

int max(bst* tree, int* value) {
    if (tree == NULL || value == NULL) {
        return EXIT_FAILURE;
    }
    if (tree->root == NULL) {
        return EXIT_FAILURE;
    }
    tree_node* dummy = tree->root;
    while (dummy->right) {
        dummy = dummy->right;
    }
    *value = dummy->value;
    return EXIT_SUCCESS; 
}

int get_size(bst* tree, int* value) {
    if (tree == NULL || value == NULL) {
        return EXIT_FAILURE;
    }
    *value = tree->number_of_nodes;
    return EXIT_SUCCESS;
}

void range_helper(tree_node* node, int min, int max) {
    if (node == NULL) return;
    range_helper(node->left, min, max);
    if (node->value <= max && node->value >= min) {
        printf("%d ", node->value);
    }
    range_helper(node->right, min, max);
}

int bst_range(bst* tree, int min, int max) {
    if (tree == NULL) return EXIT_FAILURE;
    range_helper(tree->root, min, max);
    printf("\n");
    return EXIT_SUCCESS;
}

void bst_clean(tree_node* root) {
    if (root == NULL) return;
    bst_clean(root->left);
    bst_clean(root->right);
    free(root);
}

int clear_bst(bst* tree) {
    if (tree == NULL) return EXIT_FAILURE;
    bst_clean(tree->root);
    tree->number_of_nodes = 0;
    tree->root = NULL;
    return EXIT_SUCCESS;
}

int free_bst(bst* tree) {
    if (tree == NULL) return EXIT_FAILURE;
    bst_clean(tree->root);
    free(tree);
    return EXIT_SUCCESS;
}

void print_tree(tree_node* root, int depth, char prefix) {
    if (root == NULL)
        return;
    print_tree(root->right, depth + 1, '/');

    for (int i = 0; i < depth; i++)
        printf("    ");
    if (depth > 0)
        printf("%c── ", prefix);
    printf("%d\n", root->value);

    print_tree(root->left, depth + 1, '\\');
}