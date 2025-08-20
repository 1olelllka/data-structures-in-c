#ifndef AVL
#define AVL

typedef struct _avl {
    struct _avl_node* root;
    int number_of_nodes;
} avl;

typedef struct _avl_node {
    int value;
    int height;
    struct _avl_node* right;
    struct _avl_node* left;
} avl_node;

avl* create_tree();

int insert_node(avl* tree, int value);

int search_node(avl* tree, int value, avl_node** result);

int delete_node(avl* tree, int value);

int min(avl* tree, int* res);

int max(avl* tree, int* res);

int get_node_height(avl_node* node);

int in_order_dfs(avl* tree);

int pre_order_dfs(avl* tree);

int post_order_dfs(avl* tree);

int bfs(avl* tree);

void print_avl(avl_node* root, int depth, char prefix);

int free_tree(avl* tree);

#endif