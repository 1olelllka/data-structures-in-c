#include "../include/red_black.h"
#include <stdlib.h>
#include <stdio.h>

void print_tree(node* root, int depth, char prefix) {
    if (root == NULL)
        return;
    print_tree(root->right, depth + 1, '/');

    for (int i = 0; i < depth; i++)
        printf("    ");
    if (depth > 0)
        printf("%c── ", prefix);
    printf("(%c)%d\n", root->color == RED ? 'R' : 'B', root->value);

    print_tree(root->left, depth + 1, '\\');
}

red_black_tree* create_red_black_tree() {
    red_black_tree* tree = malloc(sizeof(red_black_tree));
    if (tree == NULL) {
        perror("malloc() error");
        return NULL;
    }
    tree->number_of_nodes = 0;
    tree->root = NULL;
    return tree;
}

node* left_rotate(node* r) {
    if (r == NULL) return NULL;
    node* new_root = r->right;
    node* left_children = new_root->left;
    if (left_children) {
        left_children->parent = r;
    }
    new_root->parent = r->parent;
    if (new_root->parent) {
        if (new_root->parent->left == r) {
            new_root->parent->left = new_root;
        } else {
            new_root->parent->right = new_root;
        }
    }
    r->parent = new_root;
    new_root->left = r;
    r->right = left_children;
    return new_root;
}

node* right_rotate(node* r) {
    if (r == NULL) return NULL;
    node* new_root = r->left;
    node* right_children = new_root->right;
    if (right_children) {
        right_children->parent = r;
    }
    new_root->parent = r->parent;
    if (new_root->parent) {
        if (new_root->parent->left == r) {
            new_root->parent->left = new_root;
        } else {
            new_root->parent->right = new_root;
        }
    }
    r->parent = new_root;
    new_root->right = r;
    r->left = right_children;
    return new_root;
}

node* insert_fixup(node* root, node* new_node) {
    if (new_node->value == root->value) {
        new_node->color = BLACK;
        return new_node;
    } 
    while (new_node->color == RED && new_node->parent && new_node->parent->color == RED) {
        if (new_node->parent->parent->right != new_node->parent) {
            if (new_node->parent->parent->right && new_node->parent->parent->right->color == RED) {
                new_node->parent->parent->color = RED;
                new_node->parent->parent->right->color = BLACK;
                new_node->parent->color = BLACK;
                new_node = new_node->parent->parent;
            } else {
                if (new_node->parent->right == new_node) {
                    new_node = left_rotate(new_node->parent);
                }
                if (new_node->color == RED && new_node->color == new_node->parent->color) {
                    new_node->parent->parent->color = RED;
                    new_node->parent->color = BLACK;
                    node* tmp = right_rotate(new_node->parent->parent);
                    if (tmp->parent == NULL) {
                        root = tmp;
                    }
                } else {
                    new_node->parent->color = RED;
                    new_node->color = BLACK;
                    node* tmp = right_rotate(new_node->parent);
                    if (tmp->parent == NULL) {
                        root = tmp;
                    }
                }
            }
        } else {
            if (new_node->parent->parent->left && new_node->parent->parent->left->color == RED) {
                new_node->parent->parent->color = RED;
                new_node->parent->parent->left->color = BLACK;
                new_node->parent->color = BLACK;
                new_node = new_node->parent->parent;
            } else {
                if (new_node->parent->left == new_node) {
                        new_node = right_rotate(new_node->parent);
                    }
                if (new_node->color == RED && new_node->color == new_node->parent->color) {
                    new_node->parent->parent->color = RED;
                    new_node->parent->color = BLACK;
                    node* tmp = left_rotate(new_node->parent->parent);
                    if (tmp->parent == NULL) {
                        root = tmp;
                    }
                } else {
                    new_node->parent->color = RED;
                    new_node->color = BLACK;
                    node* tmp = left_rotate(new_node->parent);
                    if (tmp->parent == NULL) {
                        root = tmp;
                    }
                }
            }
        }
    }
    root->color = BLACK;
    return root;
}

node* insert_helper(node* root, node* new_node, int* number_of_nodes) {
    if (root == NULL) {
        *number_of_nodes += 1;
        return new_node;
    }
    new_node->parent = root;
    if (new_node->value > root->value) {
        root->right = insert_helper(root->right, new_node, number_of_nodes);
    } else if (new_node->value < root->value) {
        root->left = insert_helper(root->left, new_node, number_of_nodes);
    }
    return root;
}

int insert(red_black_tree* tree, int value) {
    if (tree == NULL) return EXIT_FAILURE;
    node* new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        perror("malloc() error");
        return EXIT_FAILURE;
    }
    new_node->value = value;
    new_node->color = RED;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    int old_number = tree->number_of_nodes;
    tree->root = insert_helper(tree->root, new_node, &tree->number_of_nodes);
    if (old_number == tree->number_of_nodes) {
        free(new_node);
        return EXIT_FAILURE;
    }
    tree->root = insert_fixup(tree->root, new_node);
    return EXIT_SUCCESS;
}

int search(red_black_tree* tree, int value, node** result) {
    if (tree == NULL) return EXIT_FAILURE;
    if (result == NULL) return EXIT_FAILURE;
    node* dummy = tree->root;
    while (dummy) {
        if (value > dummy->value) {
            dummy = dummy->right;
        } else if (value < dummy->value) {
            dummy = dummy->left;
        } else {
            *result = dummy;
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

node* get_min(node* root) {
    node* dummy = root;
    if (dummy == NULL) return NULL; 
    while (dummy->left) {
        dummy = dummy->left;
    }
    return dummy;
}

void delete_fixup(red_black_tree* tree, node* x, node* x_parent) {

    while ((x == NULL ? BLACK : x->color) == BLACK && x != tree->root) {

        if (x_parent && x_parent->left == x) {
            node* w = x_parent->right;
            if (w && w->color == RED) {
                w->color = BLACK;
                x_parent->color = RED;
                node* new_sub = left_rotate(x_parent);
                if (new_sub->parent == NULL) tree->root = new_sub;
                w = x->parent->right;
            }
            if (w && w->color == BLACK && (!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = x_parent;
                x_parent = x_parent->parent;
            } else {
                if (w && w->color == BLACK && w->right && w->right->color == BLACK) {
                    if (w->left) w->left->color = BLACK;
                    w->color = RED;
                    node* sub = right_rotate(w);
                    if (sub->parent == NULL) tree->root = sub;
                    w = x_parent->right;
                }
                w->color = x_parent->color;
                x_parent->color = BLACK;
                if (w->right) w->right->color = BLACK;
                node* sub = left_rotate(x_parent);
                if (sub->parent == NULL) tree->root = sub;
                x = tree->root;
                break;
            }
        } else { // mirroring
            node* w = x_parent->left;
            if (w && w->color == RED) {
                w->color = BLACK;
                w->parent->color = RED;
                node* new_sub = right_rotate(x_parent);
                if (new_sub->parent == NULL) tree->root = new_sub;
                w = x->parent->left;
            }
            if (w && w->color == BLACK && (!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = x_parent;
                x_parent = x_parent->parent;
            } else {
                if (w && w->color == BLACK && w->left && w->left->color == BLACK) {
                    if (w->right) w->right->color = BLACK;
                    w->color = RED;
                    node* sub = left_rotate(w);
                    if (sub->parent == NULL) tree->root = sub;
                    w = x_parent->left;
                }
                w->color = x->parent->color;
                x_parent->color = BLACK;
                node* sub = right_rotate(x_parent);
                if (sub->parent == NULL) tree->root = sub;
                x = tree->root;
                break;
            }
        }
    }
    if (x) x->color = BLACK;
}

void transplant(red_black_tree* tree, node* u, node* v) {
    if (u->parent == NULL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v) v->parent = u->parent;
}

int remove_node(red_black_tree* tree, int value) {
    if (tree == NULL) return EXIT_FAILURE;
    node* z = tree->root;
    while (z && z->value != value) {
        if (value < z->value) z = z->left;
        else z = z->right;
    }
    if (z == NULL) return EXIT_FAILURE;

    node* y = z;
    tree_color original_color = y->color;
    node* x = NULL;
    node* x_parent = NULL;
    if (z->left == NULL) {
        x = z->right;
        x_parent = z->parent;
        transplant(tree, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        x_parent = z->parent;
        transplant(tree, z, z->left);
    } else {
        y = get_min(z->right);
        original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x) x->parent = y;
            x_parent = y;
        } else {
            x_parent = y->parent;
            transplant(tree, y, y->right);
            y->right = z->right;
            if (y->right) y->right->parent = y;
        }
        transplant(tree, z, y);
        y->left = z->left;
        if (y->left) y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    tree->number_of_nodes -= 1;

    if (original_color == BLACK) {
        delete_fixup(tree, x, x_parent);
    }

    if (tree->root) tree->root->color = BLACK;
    return EXIT_SUCCESS;
}

int validate_reds_children(node* root) {
    if (!root) return EXIT_SUCCESS;
    if (root->color == RED) {
        if (root->left && root->left->color == RED) return EXIT_FAILURE;
        if (root->right && root->right->color == RED) return EXIT_FAILURE;
    }
    return validate_reds_children(root->left) && validate_reds_children(root->right);
}

int validate_black_depth(node* root, int* result) {
    if (!root) return 1;
    int left_height = validate_black_depth(root->left, result);
    int right_height = validate_black_depth(root->right, result);

    if (*result == EXIT_FAILURE) return -1;

    int curr = root->color == BLACK ? 1 : 0;
    if (left_height == right_height) {
        return left_height + curr;
    } else {
        *result = EXIT_FAILURE;
        return -1;
    }
}

int validate_tree(red_black_tree* tree) {
    if (!tree) return EXIT_FAILURE;
    if (!tree->root) return EXIT_SUCCESS; // we assume that NIL node is black, so technically it's correct
    // Rule 1: The root must be black
    if (tree->root->color != BLACK) return EXIT_FAILURE;
    // Rule 2: If a node is red, then its children are black
    if (validate_reds_children(tree->root) == EXIT_FAILURE) return EXIT_FAILURE;
    // Rule 3: All paths from a node to its NIL descendants contain the same number of black nodes
    int result = EXIT_SUCCESS;
    validate_black_depth(tree->root, &result);
    return result;
}

void clean_helper(node* root) {
    if (root == NULL) return;
    clean_helper(root->left);
    clean_helper(root->right);
    free(root);
}

int clean_tree(red_black_tree* tree) {
    if (tree == NULL) return EXIT_FAILURE;
    clean_helper(tree->root);
    tree->number_of_nodes = 0;
    tree->root = NULL;
    return EXIT_SUCCESS;
}

int free_tree(red_black_tree* tree) {
    if (tree == NULL) return EXIT_FAILURE;
    clean_helper(tree->root);
    free(tree);
    return EXIT_SUCCESS;
}