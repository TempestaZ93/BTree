#define CTEST_MAIN
#define CTEST_SEGFAULT

#define BINARY_TREE_IMPLEMENTATION
#include "BTree.h"
#include <stdlib.h>

#include "ctest.h"

CTEST_DATA(bttest) { bt_Tree *tree; };

CTEST_SETUP(bttest) { data->tree = bt_create_int(BT_NO_DELETE); }

CTEST_TEARDOWN(bttest) { bt_delete(data->tree); }

CTEST2(bttest, add1) {
    int *val = (int *)calloc(1, sizeof(int));
    *val = 4;
    bt_add(data->tree, val);
    ASSERT_EQUAL(data->tree->count, 1);
    ASSERT_EQUAL(*(int *)data->tree->root->data, 4);
}

CTEST2(bttest, add2) {
    int *val = (int *)calloc(1, sizeof(int));
    int *val2 = (int *)calloc(1, sizeof(int));
    int *val3 = (int *)calloc(1, sizeof(int));
    *val = 4;
    *val2 = 3;
    *val3 = 5;
    bt_add(data->tree, val);
    bt_add(data->tree, val2);
    bt_add(data->tree, val3);
    bt_Node *root = data->tree->root;
    ASSERT_EQUAL(data->tree->count, 3);
    ASSERT_EQUAL(*(int *)root->data, 4);
    ASSERT_EQUAL(*(int *)root->left->data, 3);
    ASSERT_EQUAL(*(int *)root->right->data, 5);
}

CTEST2(bttest, remove_leaf) {
    int *val = (int *)calloc(1, sizeof(int));
    int *val2 = (int *)calloc(1, sizeof(int));
    int *val3 = (int *)calloc(1, sizeof(int));
    *val = 4;
    *val2 = 3;
    *val3 = 5;
    bt_add(data->tree, val);
    bt_add(data->tree, val2);
    bt_add(data->tree, val3);
    bt_Node *root = data->tree->root;

    ASSERT_EQUAL(data->tree->count, 3);
    bt_remove(data->tree, val2);
    ASSERT_EQUAL(data->tree->count, 2);
}

CTEST2(bttest, remove_root) {
    int *val = (int *)calloc(1, sizeof(int));
    int *val2 = (int *)calloc(1, sizeof(int));
    int *val3 = (int *)calloc(1, sizeof(int));
    *val = 4;
    *val2 = 3;
    *val3 = 5;
    bt_add(data->tree, val);
    bt_add(data->tree, val2);
    bt_add(data->tree, val3);
    bt_Node *root = data->tree->root;

    ASSERT_EQUAL(data->tree->count, 3);
    bt_remove(data->tree, val);
    ASSERT_EQUAL(data->tree->count, 2);
    ASSERT_EQUAL(*(int *)root->data, 3);
    ASSERT_EQUAL(*(int *)root->right->data, 5);
}

CTEST2(bttest, remove_root_2) {
    int *val = (int *)calloc(1, sizeof(int));
    int *val2 = (int *)calloc(1, sizeof(int));
    int *val3 = (int *)calloc(1, sizeof(int));
    *val = 3;
    *val2 = 4;
    *val3 = 5;
    bt_add(data->tree, val);
    bt_add(data->tree, val2);
    bt_add(data->tree, val3);
    bt_Node *root = data->tree->root;
    ASSERT_EQUAL(data->tree->count, 3);
    bt_remove(data->tree, val);
    ASSERT_EQUAL(*(int *)root->data, 4);
    ASSERT_EQUAL(*(int *)root->right->data, 5);
}

CTEST2(bttest, traverse_pre_order) {
    int *val = (int *)calloc(1, sizeof(int));
    int *val2 = (int *)calloc(1, sizeof(int));
    int *val3 = (int *)calloc(1, sizeof(int));
    *val = 4;
    *val2 = 3;
    *val3 = 5;
    bt_add(data->tree, val);
    bt_add(data->tree, val2);
    bt_add(data->tree, val3);

    bt_Node **traversal = NULL;
    bt_traverse(data->tree, PRE_ORDER, &traversal);

    ASSERT_EQUAL(*(int *)traversal[0]->data, 4);
    ASSERT_EQUAL(*(int *)traversal[1]->data, 3);
    ASSERT_EQUAL(*(int *)traversal[2]->data, 5);

    free(traversal);
}

CTEST2(bttest, traverse_in_order) {
    int *val = (int *)calloc(1, sizeof(int));
    int *val2 = (int *)calloc(1, sizeof(int));
    int *val3 = (int *)calloc(1, sizeof(int));
    *val = 4;
    *val2 = 3;
    *val3 = 5;
    bt_add(data->tree, val);
    bt_add(data->tree, val2);
    bt_add(data->tree, val3);

    bt_Node **traversal = NULL;
    bt_traverse(data->tree, IN_ORDER, &traversal);

    ASSERT_EQUAL(*(int *)traversal[0]->data, 3);
    ASSERT_EQUAL(*(int *)traversal[1]->data, 4);
    ASSERT_EQUAL(*(int *)traversal[2]->data, 5);

    free(traversal);
}

CTEST2(bttest, traverse_post_order) {
    int *val = (int *)calloc(1, sizeof(int));
    int *val2 = (int *)calloc(1, sizeof(int));
    int *val3 = (int *)calloc(1, sizeof(int));
    *val = 4;
    *val2 = 3;
    *val3 = 5;
    bt_add(data->tree, val);
    bt_add(data->tree, val2);
    bt_add(data->tree, val3);

    bt_Node **traversal = NULL;
    bt_traverse(data->tree, POST_ORDER, &traversal);

    ASSERT_EQUAL(*(int *)traversal[0]->data, 3);
    ASSERT_EQUAL(*(int *)traversal[1]->data, 5);
    ASSERT_EQUAL(*(int *)traversal[2]->data, 4);

    free(traversal);
}

CTEST2(bttest, balance) {
    int *val = (int *)calloc(1, sizeof(int));
    int *val2 = (int *)calloc(1, sizeof(int));
    int *val3 = (int *)calloc(1, sizeof(int));
    int *val4 = (int *)calloc(1, sizeof(int));
    int *val5 = (int *)calloc(1, sizeof(int));
    int *val6 = (int *)calloc(1, sizeof(int));
    *val = 1;
    *val2 = 2;
    *val3 = 3;
    *val4 = 4;
    *val5 = 5;
    *val6 = 6;
    bt_add(data->tree, val);
    bt_add(data->tree, val2);
    bt_add(data->tree, val3);
    bt_add(data->tree, val4);
    bt_add(data->tree, val5);
    bt_add(data->tree, val6);

    ASSERT_TRUE(bt_is_balanced(data->tree));
}
