

typedef struct _red_black {
    struct _node* root;
    int number_of_nodes;
} red_black_tree;

typedef enum {
    BLACK,
    RED
} tree_color;

typedef struct _node {
    int value;
    tree_color color;
    struct _node* left;
    struct _node* right;
    struct _node* parent;
} node;

red_black_tree* create_red_black_tree();

int insert(red_black_tree* tree, int value);

int search(red_black_tree* tree, int value, node** result);

int remove_node(red_black_tree* tree, int value);

int clean_tree(red_black_tree* tree);

int free_tree(red_black_tree* tree);

void print_tree(node* root, int depth, char prefix);