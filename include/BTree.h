#ifndef _B_TREE_
#define _B_TREE_

#include <stdbool.h>
#include <stddef.h>

#define bt_max(x, y) (x > y ? x : y)

/**
 * @brief Struct that defines a node in the binary tree.
 */
struct bt_Node {
    /**
     * @brief Pointer to the left child of this node (NULL if empty).
     */
    struct bt_Node *left;
    /**
     * @brief Pointer to the right child of this node (NULL if empty).
     */
    struct bt_Node *right;
    /**
     * @brief pointer to the data held by this node.
     * This pointer is used for the compare, delete and to_str method of the binary
     * tree.
     */
    void *data;
};

struct bt_Node;
typedef struct bt_Node bt_Node;

/**
 * @brief Struct that defines the binary tree and holds necessary methods for node handling.
 *
 * For simple usage with primitive data types the tree offers utility creation and print methods.
 *
 * @example Simple usage of bt_Tree.
 *   bt_Tree *tree = bt_create_int(BT_NO_DELETE);
 *   int val1 = 3;
 *   int val2 = 4;
 *   int val3 = 2;
 *   bt_add(tree, &val1);
 *   bt_add(tree, &val2);
 *   bt_add(tree, &val3);
 *
 *   bt_print_int(tree);
 *   bt_delete(tree);
 */
struct bt_Tree {
    /**
     * Root node of this tree it uses as entry point for all actions.
     */
    bt_Node *root;
    /**
     * Counter used for keeping track of the number of nodes in this tree.
     */
    size_t count;
    /**
     * Comparison function used for inserting and deleting nodes.
     * d1 < d2 return -1 .
     * d1 = d2 return  0 .
     * d1 > d2 return  1 .
     */
    int (*compare)(void *d1, void *d2);
    /**
     * Deletion function for a node's data.
     */
    void (*delete)(void *data);
};

struct bt_Tree;
typedef struct bt_Tree bt_Tree;

/**
 * @brief Strategies used to walk through a tree.
 */
typedef enum {
    // current -> left -> right
    PRE_ORDER,
    // left -> current -> right (sorted)
    IN_ORDER,
    // left -> right -> current
    POST_ORDER
} TraversalStrategy;

void BT_TRIVIAL_DELETE(void *data);
void BT_NO_DELETE(void *data);

/**
 * @brief Creates an empty binary tree with the compare function to determine order.
 *
 * @param compare Comparison function used to order and compare of two data pointers.
 * d1 < d2 return -1 .
 * d1 = d2 return  0 .
 * d1 > d2 return  1 .
 * @param delete Deletion function used to free a node's data pointer when the tree is deleted. In
 * case you only use pointers that can be trivially freed, provide BT_TRIVIAL_DELETE. In case you do
 * not want to delete the data, provide BT_NO_DELETE.
 *
 * @return pointer to the created tree.
 */
bt_Tree *bt_create(int (*compare)(void *d1, void *d2), void (*delete)(void *data));

/**
 * @brief Creates an empty binary tree for integer number values.
 *
 * @param delete Deletion function used to free a node's data pointer when the tree is deleted. In
 * case you only use pointers that can be trivially freed, provide BT_TRIVIAL_DELETE. In case you do
 * not want to free the data, provide BT_NO_DELETE.
 *
 * @return pointer to the created tree.
 */
bt_Tree *bt_create_int(void (*delete)(void *data));

/**
 * @brief Creates an empty binary tree for floating point number values.
 *
 * @param delete Deletion function used to free a node's data pointer when the tree is deleted. In
 * case you only use pointers that can be trivially freed, provide BT_TRIVIAL_DELETE. In case you do
 * not want to free the data, provide BT_NO_DELETE.
 *
 * @return pointer to the created tree.
 */
bt_Tree *bt_create_float(void (*delete)(void *data));

/**
 * @brief Adds a new node holding data to the tree.
 *
 * @param tree pointer to a tree to add this data to.
 * @param data pointer to the data to add.
 *
 * @return true if the data was added or false otherwise.
 */
bool bt_add(bt_Tree *tree, void *data);
/**
 * @brief Removes the node holding data from the tree.
 *
 * @param tree pointer to a tree to remove data from.
 * @param data pointer to remove.
 *
 * @return true if the data was removed or false otherwise.
 */
bool bt_remove(bt_Tree *tree, void *data);

/**
 * @brief Traverses tree according to strategy used and writes the result in the list pointer.
 *
 * @param tree pointer to a tree to traverse.
 * @param strategy strategy to use (@see TraversalStrategy)
 * @param list pointer to a list of node pointers.
 * This list is dynamically allocated and needs to be freed by hand.
 *
 * @example Simple but complete usage of bt_traverse.
 *   bt_Tree *tree = bt_create_int(BT_NO_DELETE);
 *   int val1 = 3;
 *   int val2 = 4;
 *   int val3 = 2;
 *   bt_add(tree, &val1);
 *   bt_add(tree, &val2);
 *   bt_add(tree, &val3);
 *   bt_Node **list = NULL;
 *   bt_traverse(tree, IN_ORDER, &list);
 *   size_t len = tree->count;
 *   int idx;
 *   for (idx = 0; idx < len; idx++) {
 *       printf("%d, ", *(int *)list[idx]->data);
 *   }
 *   free(list);
 *   bt_delte(tree);
 */
void bt_traverse(bt_Tree *tree, TraversalStrategy strategy, bt_Node ***list);

/**
 * @brief Tests if tree is completely balanced.
 * This required all nodes in the tree to be balanced.
 *
 * @param tree pointer to a tree to check for balance.
 *
 * @return true if tree is balanced or false otherwise.
 */
bool bt_is_balanced(bt_Tree *tree);

/**
 * @brief Balances tree using left and right rotations.
 *
 * @param tree pointer to a tree to balance.
 */
void bt_balance(bt_Tree *tree);

/**
 * @brief prints tree to STDOUT using the given function for node data.
 *
 * @param tree pointer to a tree to print.
 * @param to_str function used to convert data to a str.
 * The given string has a capacity of 128 characters.
 * Be carefull, the string pointer is reset for every node. So do not put your data in there.
 */
void bt_print(bt_Tree *tree, void (*to_str)(void *, char *));

/**
 * @brief prints the tree interpreting the data as integer numbers.
 *
 * @param tree pointer to a tree to print
 */
void bt_print_int(bt_Tree *tree);

/**
 * @brief prints the tree interpreting the data as floating point numbers.
 *
 * @param tree pointer to a tree to print
 */
void bt_print_float(bt_Tree *tree);

/**
 * @brief deletes the tree and its data using the delete function set in bt_create.
 * The tree pointer is set to NULL after deletion.
 *
 * @param tree pointer to a tree to delete.
 */
void bt_delete(bt_Tree *tree);

#endif // _B_TREE_

#ifdef BINARY_TREE_IMPLEMENTATION
#ifndef _BIN_TREE_IMPL_
#define _BIN_TREE_IMPL_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// helper methods definition
static int _cmp_int(void *d1, void *d2);
static int _cmp_float(void *d1, void *d2);
static void _int_to_str(void *data, char *str);
static void _float_to_str(void *data, char *str);
static int _add(bt_Node **node, bt_Node *parent, void *data, int (*compare)(void *d1, void *d2));
static void _delete(bt_Tree *tree);
static void _clear(bt_Node **root);
static int _remove(bt_Node **node, void *data, int (*compare)(void *d1, void *d2));
static int _traverse(bt_Node *node, TraversalStrategy strategy, bt_Node **array, size_t idx);
static size_t _depth_at(bt_Node *node);
static bool _is_balanced(bt_Node *node);
static void _balance(bt_Node **node);
static void _rotate_left(bt_Node **node);
static void _rotate_right(bt_Node **node);
static void _print(bt_Node *node, void (*to_str)(void *, char *), int level);

bt_Tree *bt_create(int (*compare)(void *d1, void *d2), void (*delete)(void *data)) {
    bt_Tree *tree = (bt_Tree *)malloc(sizeof(bt_Tree));
    tree->root = NULL;
    tree->count = 0;
    tree->compare = compare;
    tree->delete = delete;
    return tree;
}

bt_Tree *bt_create_int(void (*delete)(void *data)) { return bt_create(&_cmp_int, delete); }
bt_Tree *bt_create_float(void (*delete)(void *data)) { return bt_create(&_cmp_float, delete); }

bool bt_add(bt_Tree *tree, void *data) {
    size_t added = _add(&tree->root, NULL, data, tree->compare);
    tree->count += added;
    _balance(&tree->root);
    if (added == 1) {
        return true;
    } else {
        return false;
    }
}

bool bt_remove(bt_Tree *tree, void *data) {
    size_t removed = _remove(&tree->root, data, tree->compare);
    tree->count -= removed;
    _balance(&tree->root);
    if (removed == 1) {
        return true;
    } else {
        return false;
    }
}

void bt_traverse(bt_Tree *tree, TraversalStrategy strategy, bt_Node ***traversal) {
    *traversal = (bt_Node **)malloc(tree->count * sizeof(bt_Node *));
    size_t traversed = _traverse(tree->root, strategy, *traversal, 0);
}

bool bt_is_balanced(bt_Tree *tree) { return _is_balanced(tree->root); }

void bt_balance(bt_Tree *tree) { _balance(&tree->root); }

void bt_print(bt_Tree *tree, void (*to_str)(void *, char *)) {
    _print(tree->root, to_str, 0);
    printf("\n");
}

void bt_print_int(bt_Tree *tree) { bt_print(tree, _int_to_str); }

void bt_print_float(bt_Tree *tree) { bt_print(tree, _float_to_str); }

void bt_delete(bt_Tree *tree) { _delete(tree); }

void BT_TRIVIAL_DELETE(void *data) { free(data); }
void BT_NO_DELETE(void *data) {}
// helper methods implementation

static int _cmp_int(void *d1, void *d2) {
    int i1 = *((int *)d1);
    int i2 = *((int *)d2);

    if (i1 < i2) {
        return -1;
    } else if (i1 == i2) {
        return 0;
    } else {
        return 1;
    }
}

static int _cmp_float(void *d1, void *d2) {
    float f1 = *((float *)d1);
    float f2 = *((float *)d2);

    if (f1 - f2 > 0.0001) {
        return -1;
    } else if (f1 - f2 < 0.0001 && f1 - f2 > -0.0001) {
        return 0;
    } else {
        return 1;
    }
}

static void _int_to_str(void *data, char *str) { sprintf(str, "%d", *(int *)data); }

static void _float_to_str(void *data, char *str) { sprintf(str, "%f", *(float *)data); }

static int _add(bt_Node **node, bt_Node *parent, void *data, int (*compare)(void *d1, void *d2)) {
    if (*node == NULL) {
        *node = (bt_Node *)malloc(sizeof(bt_Node));
        bt_Node *nod = *node;
        nod->data = data;
        nod->left = NULL;
        nod->right = NULL;
        return 1;
    }

    int cmp_result = compare(data, (*node)->data);

    if (cmp_result <= -1) {
        return _add(&(*node)->left, parent, data, compare);
    } else if (cmp_result >= 1) {
        return _add(&(*node)->right, parent, data, compare);
    } else {
        return 0;
    }
}

static void _clear(bt_Node **root) {
    bt_Node *node = *root;
    if (node->left != NULL) {
        node->data = node->left->data;
        _clear(&node->left);
    } else if (node->right != NULL) {
        node->data = node->right->data;
        _clear(&node->right);
    } else {
        free(node);
        *root = NULL;
    }
}
static int _remove(bt_Node **node, void *data, int (*compare)(void *d1, void *d2)) {
    if (*node == NULL) {
        return 0;
    }

    int cmp_result = compare(data, (*node)->data);

    if (cmp_result == 0) {
        _clear(node);
        return 1;
    } else if (cmp_result <= -1) {
        return _remove(&(*node)->left, data, compare);
    } else {
        return _remove(&(*node)->right, data, compare);
    }
}

static int _traverse(bt_Node *node, TraversalStrategy strategy, bt_Node **array, size_t idx) {
    if (node == NULL) {
        return idx;
    }

    switch (strategy) {
    case PRE_ORDER:
        array[idx++] = node;
        idx = _traverse(node->left, strategy, array, idx);
        idx = _traverse(node->right, strategy, array, idx);
        break;
    case IN_ORDER:
        idx = _traverse(node->left, strategy, array, idx);
        array[idx++] = node;
        idx = _traverse(node->right, strategy, array, idx);
        break;
    case POST_ORDER:
        idx = _traverse(node->left, strategy, array, idx);
        idx = _traverse(node->right, strategy, array, idx);
        array[idx++] = node;
        break;
    }

    return idx;
}

static size_t _depth_at(bt_Node *node) {
    if (node == NULL) {
        return 0;
    }

    size_t left_depth = 0;
    if (node->left != NULL) {
        left_depth = _depth_at(node->left);
    }

    size_t right_depth = 0;
    if (node->right != NULL) {
        right_depth = _depth_at(node->right);
    }

    return bt_max(left_depth, right_depth) + 1;
}

static bool _is_balanced(bt_Node *node) {
    if (node == NULL) {
        return true;
    }

    int left_depth = 0;
    if (node->left != NULL) {
        left_depth = (int)_depth_at(node->left);
    }

    int right_depth = 0;
    if (node->right != NULL) {
        right_depth = (int)_depth_at(node->right);
    }

    return abs(left_depth - right_depth) <= 1 && _is_balanced(node->left) &&
           _is_balanced(node->right);
}

static void _balance(bt_Node **rootPtr) {
    if (*rootPtr == NULL) {
        return;
    }

#define HISTORY_LEN 5
    size_t left_history[HISTORY_LEN] = {0};
    size_t right_history[HISTORY_LEN] = {0};
    size_t history_curr = 0;

    int left_depth;
    int right_depth;
    while (true) {
        bt_Node *root = *rootPtr;
        if (root->left != NULL) {
            left_depth = (int)_depth_at(root->left);
        } else {
            left_depth = 0;
        }

        if (root->right != NULL) {
            right_depth = (int)_depth_at(root->right);
        } else {
            right_depth = 0;
        }

        if (left_history[0] == left_depth && right_history[0] == right_depth) {
            break;
        }

        if (right_depth > left_depth + 1) {
            _rotate_left(rootPtr);
        } else if (left_depth > right_depth + 1) {
            _rotate_right(rootPtr);
        } else {
            break;
        }

        left_history[history_curr] = left_depth;
        right_history[history_curr] = right_depth;
        history_curr = history_curr + 1 % HISTORY_LEN;
    }

    _balance(&(*rootPtr)->left);
    _balance(&(*rootPtr)->right);
}

static void _rotate_left(bt_Node **rootPtr) {
    if (*rootPtr == NULL) {
        return;
    }

    bt_Node *root = *rootPtr;
    bt_Node *pivot = root->right;
    bt_Node *pivotChild = pivot->left;

    root->right = pivotChild;
    pivot->left = root;
    *rootPtr = pivot;
}

static void _rotate_right(bt_Node **rootPtr) {
    bt_Node *root = *rootPtr;
    bt_Node *pivot = root->left;
    bt_Node *pivotChild = pivot->right;

    root->left = pivotChild;
    pivot->right = root;
    *rootPtr = pivot;
}

static void _print(bt_Node *node, void (*to_str)(void *data, char *str), int level) {
    enum { DATA_STR_LEN = 129 };
    static char data_str[DATA_STR_LEN];

    if (node == NULL) {
        return;
    }

    _print(node->left, to_str, level + 1);

    printf("\n");
    size_t depth;
    for (depth = 0; depth < level; depth++) {
        printf("\t");
    }

    memset(data_str, 0, DATA_STR_LEN);
    to_str(node->data, data_str);
    printf("%s", data_str);

    _print(node->right, to_str, level + 1);
}

static void _delete(bt_Tree *tree) {
    bt_Node **traversal = NULL;
    bt_Node *current;
    size_t idx = 0;

    bt_traverse(tree, POST_ORDER, &traversal);

    for (idx = 0; idx < tree->count; idx++) {
        current = traversal[idx];
        if (current == NULL) {
            continue;
        }
        if (current->data != NULL) {
            tree->delete (current->data);
        }
        free(current);
        current = NULL;
    }
    free(traversal);
    free(tree);
    tree = NULL;
}
#endif // _BIN_TREE_IMPL_
#endif // BINARY_TREE_IMPLEMENTATION
