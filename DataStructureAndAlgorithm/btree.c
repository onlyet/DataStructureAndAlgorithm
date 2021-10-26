#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define HalfOrder 3

typedef int KeyType;

typedef struct _btree_node {
    KeyType* keys;	                // 关键字数组
    int keyNum;				        // 关键字数量
    struct _btree_node** childs;    // 子节点数组
    int isLeaf				        // 是否叶子节点
} btree_node;

typedef struct _btree {
    btree_node* root;
    int         order;               // 几阶
} btree;

btree_node* btree_create(/*btree_node* root*/) {

    btree_node* n = (btree_node*)calloc(1, sizeof(btree_node));
    assert(NULL != n);


}

int main() {
    btree* t = (btree*)malloc(sizeof(btree));
    assert(NULL != t);

    t->order = HalfOrder * 2;
    t->root = (btree_node*)calloc(1, sizeof(btree_node));
    assert(NULL != t->root);

    btree_create(t);

}