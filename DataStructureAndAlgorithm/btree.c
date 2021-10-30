#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define HalfOrder 3

typedef int KeyType;

typedef struct _btree_node {
    KeyType* keys;	                // 关键字数组
    int key_num;				    // 关键字数量
    struct _btree_node** childs;    // 子节点数组
    int is_leaf;				    // 是否叶子节点
} btree_node;

typedef struct _btree {
    btree_node* root;
    int         half_order;         // 阶数的二分之一
} btree;

btree_node* btree_create_node(int half_order, int is_leaf) {

    btree_node* n = (btree_node*)calloc(1, sizeof(btree_node));
    assert(NULL != n);

    n->keys = (KeyType*)calloc(1, sizeof(KeyType) * (2 * half_order - 1));
    assert(NULL != n->keys);

    n->childs = (btree_node**)calloc(1, sizeof(btree_node*) * (2 * half_order));
    assert(NULL != n->childs);

    n->key_num = 0;
    n->is_leaf = is_leaf;

    return n;
}

void btree_destroy_node(btree_node* n) {
    if (n) {
        if (n->keys) {
            free(n->keys);
            n->keys = NULL;
        }
        if (n->childs) {
            free(n->childs);
            n->childs = NULL;
        }
    }
}

void btree_create(btree* t, int half_order) {
    t->root = btree_create_node(half_order, 1);
    t->half_order = half_order;
}

int main() {
    btree t;

    btree_create(&t, HalfOrder);
}