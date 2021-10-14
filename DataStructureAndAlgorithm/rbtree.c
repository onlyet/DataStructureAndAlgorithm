
/*
 * ������ʣ�
 * 1. �ڵ�Ǻ켴��
 * 2. ���ڵ��Ǻ�ɫ
 * 3. Ҷ�ӽڵ㶼�Ǻ�ɫ��nil��
 * 4. ��ɫ�ڵ���������Ӷ��Ǻ�ɫ��û�������ĺ�ڵ㣩
 * 5. ��һ�ڵ㣬��������Ҷ�ӽڵ�����м�·���ĺ�ɫ�ڵ�����ͬ���ڸ���ͬ��
*/

#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 2

typedef int DataType;
// compare����

typedef struct _RBTreeNode {
    int                 color;
    DataType            data;
    struct _RBTreeNode* lchild;
    struct _RBTreeNode* rchild;
    struct _RBTreeNode* parent;
} RBTreeNode;

typedef struct _RBTree {
    RBTreeNode* root;
    RBTreeNode* nil;
} RBTree;

// ���ڵ���x
void rotate_left(RBTree* t, RBTreeNode* x) {
    RBTreeNode* y = x->rchild;
    x->rchild = y->lchild;

    // ��һ������
    if (y->lchild != t->nil) {
        y->lchild->parent = x;
    }
    y->lchild = x;

    // ��һ��û����������ڴ�����һ��ָ��x������ͨ��ָ��xֱ�Ӹı�root�ڵ㣬�������xָ����ڵ����޸�rootָ��Ϊ�µĸ��ڵ�
    if (x->parent == t->nil) {
        t->root = y;
    }
    else if (x == x->parent->lchild) {
        x->parent->lchild = y;
    }
    else {
        x->parent->rchild = y;
    }

    y->parent = x->parent;
    x->parent = y;
}

// ���ڵ���y
// ��rotate_left�е�x��y��������lchild��rchild����
void rotate_right(RBTree* t, RBTreeNode* y) {
    RBTreeNode* x = y->lchild;
    y->lchild = x->rchild;
    if (x->rchild != t->nil) {
        x->rchild->parent = y;
    }

    x->rchild = y;

    if (y->parent == t->nil) {
        t->root = x;
    }
    else if (y == y->parent->lchild) {
        y->parent->lchild = x;
    }
    else {
        y->parent->rchild = x;
    }

    x->parent = y->parent;
    y->parent = x;
}

RBTreeNode* uncle(RBTreeNode* x) {
    if (x->parent == x->parent->parent->lchild) {
        return x->parent->parent->rchild;
    }
    else {
        return x->parent->parent->lchild;
    }
}

void balance(RBTree* t, RBTreeNode* x) {
    // case 1
    if (x->parent == t->nil) {
        x->color = BLACK;
        return;
    }
    // case 2
    if (BLACK == x->parent->color) {
        x->color = RED;
        return;
    }

    // ���ڵ��Ǻ�ɫ�����游�ڵ㣨���Ǻ�ɫ��

    RBTreeNode* u = uncle(x);
    // case 3
    if (RED == u->color) {
        x->parent->color = BLACK;
        u->color = BLACK;
        x->parent->parent->color = RED;
        x->color = RED;
        x = x->parent->parent;
        balance(t, x);
    }
    else {
        if (x == x->parent->lchild) {
            // case 4
            // LL
            if (x->parent == x->parent->parent->lchild) {
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                x->color = RED;
                rotate_right(t, x->parent->parent);
            }
            // case 5
            // RL
            else {
                x->parent->parent->color = RED;
                x->color = BLACK;
                rotate_right(t, x->parent);
                // ������x->parent����x->parent->parent?
                rotate_left(t, x->parent);
            }
        }
        else {
            // case 4
            // RR
            if (x->parent == x->parent->parent->rchild) {
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                x->color = RED;
                rotate_left(t, x->parent->parent);
            }
            // case 5
            // LR
            else {
                x->parent->parent->color = RED;
                x->color = BLACK;
                rotate_left(t, x->parent);
                // ������x->parent����x->parent->parent?
                rotate_right(t, x->parent);
            }
        }
    }
}

// insert
void insert(RBTree* t, DataType data) {
    RBTreeNode* x = t->root;
    RBTreeNode* y = x;
    while (x != t->nil) {
        y = x;
        if (x->data > data) {
            x = x->lchild;
        }
        else if (x->data < data) {
            x = x->rchild;
        }
        else {
            return;
        }
    }

    // y�ǲ���ڵ�ĸ��ڵ㣬x�ǲ���ڵ�
    x = (RBTreeNode*)malloc(sizeof(RBTreeNode));
    x->data = data;
    x->lchild = t->nil;
    x->rchild = t->nil;
    if (y != t->nil) {
        if (y->data > data) {
            y->lchild = x;
        }
        else {
            y->rchild = x;
        }
    }
    else {
        t->root = x;
    }
    x->parent = y;

    balance(t, x);
}

// delete

void print(RBTree* t, RBTreeNode* root) {
    if (root == t->nil) {
        return;
    }

    print(t, root->lchild);
    printf("%d %s\n", root->data, root->color == RED ? "��ɫ" : "��ɫ");
    print(t, root->rchild);
}

// main
int main() {
    RBTree t;
    t.nil = (RBTreeNode*)malloc(sizeof(RBTreeNode));
    t.nil->color = BLACK;
    t.nil->lchild = NULL;
    t.nil->rchild = NULL;
    t.nil->parent = NULL;
    t.root = t.nil;

    DataType a[] = { 11,32, 23, 54, 15, 66, 44, 99, 100, 8};

    int i;
    int len = sizeof(a) / sizeof(DataType);
    for (i = 0; i < len; ++i) {
        insert(&t, a[i]);
    }

    print(&t, t.root);
    printf("\n");

    free(t.nil);
    t.nil = NULL;

    system("pause");
    return 0;
}