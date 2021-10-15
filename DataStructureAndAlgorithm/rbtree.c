
/*
 * ������ʣ�
 * 1. �ڵ�Ǻ켴��
 * 2. ���ڵ��Ǻ�ɫ
 * 3. Ҷ�ӽڵ㶼�Ǻ�ɫ��nil��
 * 4. ��ɫ�ڵ���������Ӷ��Ǻ�ɫ��û�������ĺ�ڵ㣩
 * 5. ��һ�ڵ㣬��������Ҷ�ӽڵ�����м�·���ĺ�ɫ�ڵ�����ͬ���ڸ���ͬ��

 * �Ƚϵ���key

*/

#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 2

typedef int KeyType;
// compare����

typedef struct _RBTreeNode {
    int                 color;
    struct _RBTreeNode* lchild;
    struct _RBTreeNode* rchild;
    struct _RBTreeNode* parent;
    KeyType             key;
    void*               value;
} RBTreeNode;

typedef struct _RBTree {
    RBTreeNode* root;
    RBTreeNode* nil;
} RBTree;

// ���ڵ���x
void rbtree_rotate_left(RBTree* t, RBTreeNode* x) {
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
// ��rbtree_rotate_left�е�x��y��������lchild��rchild����
void rbtree_rotate_right(RBTree* t, RBTreeNode* y) {
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

// x�ǲ���ڵ�
void rbtree_insert_balance(RBTree* t, RBTreeNode* x) {
    // case 1: x�Ǹ��ڵ㣬���
    if (x->parent == t->nil) {
        x->color = BLACK;
        return;
    }
    // case 2: x�ĸ����Ǻ�ɫ��x���ֺ�ɫ
    if (BLACK == x->parent->color) {
        x->color = RED;
        return;
    }

    // ���ڵ��Ǻ�ɫ�����游�ڵ㣨���Ǻ�ɫ��

    RBTreeNode* u = uncle(x);

    /* case 3 
     * ���ڵ����ڵ㶼�Ǻ�ɫ��������ڣ��游�ڵ��죬x���ֺ�ɫ
     * x�Ǻ�ɫ���������游������ɫ���ڸ�û�б䣬û���ƻ�����5
     * �游�ڵ��Ǻ�ɫ���游�ĸ��׿����Ǻ�ɫ��nil��Ϊ�˲��ƻ�����2������4��
     * ������ڵ��Ϊ�游�ڵ㣬����������
    */
    if (RED == u->color) {
        x->parent->color = BLACK;
        u->color = BLACK;
        x->parent->parent->color = RED;
        x->color = RED;
        x = x->parent->parent;
        rbtree_insert_balance(t, x);
    }
    // ���ڵ��Ǻ�ɫ����ڵ��Ǻ�ɫ
    else {
        if (x->parent == x->parent->parent->lchild) {
            /* case 4
             * LL�ͣ����游�ڵ�����
             * �����ڵ��Ϊ��ɫ���游�ڵ��Ϊ��ɫ
             * ��תǰͨ��ԭ�游�ڵ��·������ת��ͨ�����ڵ㣬�ڸ߲���
            */
            if (x == x->parent->lchild) {
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                x->color = RED;
                rbtree_rotate_right(t, x->parent->parent);
            }
            /* case 5
             * LR�ͣ��ȶԸ��ڵ������ٶ��游�ڵ�����
             * ������ڵ�x��Ϊ��ɫ���游�ڵ��Ϊ��ɫ
             * ��תǰͨ��ԭ�游�ڵ��·������ת��ͨ������ڵ�x���ڸ߲���
            */
            else {
                x->parent->parent->color = RED;
                x->color = BLACK;
                rbtree_rotate_left(t, x->parent);
                // ������תx���游���x�ĸ���
                rbtree_rotate_right(t, x->parent);
            }
        }
        // ��ס����LL��LR�ͣ������RR��RL�ͣ�ֻ��Ҫ�����Һ��ӻ�������������������
        else {
            /* case 6
             * RR�ͣ����游�ڵ�����
             * �����ڵ��Ϊ��ɫ���游�ڵ��Ϊ��ɫ
             * ��תǰͨ��ԭ�游�ڵ��·������ת��ͨ�����ڵ㣬�ڸ߲���
            */
            if (x == x->parent->rchild) {
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                x->color = RED;
                rbtree_rotate_left(t, x->parent->parent);
            }
            /* case 7
             * RL�ͣ��ȶԸ��ڵ������ٶ��游�ڵ�����
             * ������ڵ�x��Ϊ��ɫ���游�ڵ��Ϊ��ɫ
             * ��תǰͨ��ԭ�游�ڵ��·������ת��ͨ������ڵ�x���ڸ߲���
            */
            else {
                x->parent->parent->color = RED;
                x->color = BLACK;
                rbtree_rotate_right(t, x->parent);
                // ������תx���游���x�ĸ���
                rbtree_rotate_left(t, x->parent);
            }
        }
    }
}

void rbtree_insert(RBTree* t, RBTreeNode* n) {
    RBTreeNode* x = t->root;
    RBTreeNode* y = x;
    while (x != t->nil) {
        y = x;
        if (x->key > n->key) {
            x = x->lchild;
        }
        else if (x->key < n->key) {
            x = x->rchild;
        }
        else {
            return;
        }
    }

    if (y != t->nil) {
        if (y->key > n->key) {
            y->lchild = n;
        }
        else {
            y->rchild = n;
        }
    }
    else {
        t->root = n;
    }

    n->parent = y;

    rbtree_insert_balance(t, n);
}

// delete

void print(RBTree* t, RBTreeNode* root) {
    if (root == t->nil) {
        return;
    }

    print(t, root->lchild);
    printf("%d %s\n", root->key, root->color == RED ? "��ɫ" : "��ɫ");
    print(t, root->rchild);
}

// main
int main() {
    RBTree t;
    t.nil = (RBTreeNode*)malloc(sizeof(RBTreeNode));
    t.nil->color = BLACK;
    t.root = t.nil;
    t.nil->lchild = NULL;
    t.nil->rchild = NULL;
    t.nil->parent = NULL;

    KeyType a[] = { 11, 32, 23, 54, 15, 66, 44, 99, 100, 8};

    int i;
    int len = sizeof(a) / sizeof(KeyType);
    for (i = 0; i < len; ++i) {
        RBTreeNode* n = (RBTreeNode*)malloc(sizeof(RBTreeNode));
        n->key = a[i];
        n->value = NULL;
        n->lchild = t.nil;
        n->rchild = t.nil;
        rbtree_insert(&t, n);
    }

    print(&t, t.root);
    printf("\n");

    free(t.nil);
    t.nil = NULL;

    system("pause");
    return 0;
}