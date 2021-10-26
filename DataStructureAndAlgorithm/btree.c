#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define HalfOrder 3

typedef int KeyType;

typedef struct _btree_node {
    KeyType* keys;	                // �ؼ�������
    int keyNum;				        // �ؼ�������
    struct _btree_node** childs;    // �ӽڵ�����
    int isLeaf				        // �Ƿ�Ҷ�ӽڵ�
} btree_node;

typedef struct _btree {
    btree_node* root;
    int         order;               // ����
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