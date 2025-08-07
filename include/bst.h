#ifndef BST
#define BST

typedef struct _bst {
    struct _tree_node* root;
    int number_of_nodes;
} bst;

typedef struct _tree_node {
    int value;
    struct _tree_node* right;
    struct _tree_node* left;
} tree_node;

bst* create_bst();

int insert_node(bst* tree, int item);

int remove_node(bst* tree, int item);

int search_node(bst* tree, int item, tree_node** node);

int in_order_dfs(bst* tree);

int preorder_dfs(bst* tree);

int postorder_dfs(bst* tree);

int bfs(bst* tree);

int min(bst* tree, int* value);

int max(bst* tree, int* value);

int get_size(bst* tree, int* value);

int get_height(bst* tree, int* value);

int bst_range(bst* tree, int min, int max);

void print_tree(tree_node* root, int depth, char prefix);

int clear_bst(bst* tree);

int free_bst(bst* tree);

#endif