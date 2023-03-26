#define BINARY_TREE_IMPLEMENTATION
#include "BTree.h"
#include "example.h"

int main(int argc, char *argv[]) {
    bt_Tree *tree = bt_create(cmp_data, BT_NO_DELETE);
    bt_add(tree, "lorem ipsum");
    bt_add(tree, "lorem ipsum dolor sit amet");
    bt_add(tree, "consectetur adipiscing elit");
    bt_add(tree, "praesent molestie vitae erat quis porttitor");
    bt_add(tree, "sed id posuere ligula");
    bt_add(tree, "in aliquam accumsan nisl vitae varius");
    bt_add(tree, "morbi maximus quam quis metus suscipit");
    bt_add(tree, "ac dignissim elit finibus");
    bt_add(tree, "ac dignissim elit finibus");
    bt_add(tree, "etiam porttitor lorem ut sapien rhoncus");

    bt_remove(tree, "lorem ipsum");

    bt_Node **in_order = NULL;
    bt_traverse(tree, IN_ORDER, &in_order);

    size_t len = tree->count;
    size_t idx;
    for (idx = 0; idx < len; idx++) {
        bt_Node *curr = in_order[idx];
        printf("%s\n", (char *)curr->data);
    }

    free(in_order);

    bt_delete(tree);

    bt_Tree *int_tree = bt_create_int(BT_NO_DELETE);
    int val1 = 1;
    int val2 = 2;
    int val3 = 3;
    int val4 = 4;
    int val5 = 5;
    int val6 = 6;
    int val7 = 7;
    int val8 = 8;
    int val9 = 9;
    int val10 = 10;
    int val11 = 11;
    int val12 = 12;
    int val13 = 13;
    int val14 = 14;
    int val15 = 15;

    bt_add(int_tree, &val1);
    bt_add(int_tree, &val2);
    bt_add(int_tree, &val3);
    bt_add(int_tree, &val4);
    bt_add(int_tree, &val5);
    bt_add(int_tree, &val6);
    bt_add(int_tree, &val7);
    bt_add(int_tree, &val8);
    bt_add(int_tree, &val9);
    bt_add(int_tree, &val10);
    bt_add(int_tree, &val11);
    bt_add(int_tree, &val12);
    bt_add(int_tree, &val13);
    bt_add(int_tree, &val14);
    bt_add(int_tree, &val15);

    bt_print_int(int_tree);

    bt_delete(int_tree);

    return 0;
}
