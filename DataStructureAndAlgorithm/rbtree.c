
/*
 * 五个性质：
 * 1. 节点非红即黑
 * 2. 根节点是黑色
 * 3. 叶子节点都是黑色（nil）
 * 4. 红色节点的两个孩子都是黑色（没有连续的红节点）
 * 5. 任一节点，经过它到叶子节点的所有简单路径的黑色节点树相同（黑高相同）

 * 比较的是key

*/

#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 2

typedef int KeyType;
// compare函数

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

// 父节点是x
void rbtree_rotate_left(RBTree* t, RBTreeNode* x) {
    RBTreeNode* y = x->rchild;
    x->rchild = y->lchild;

    // 这一步忘了
    if (y->lchild != t->nil) {
        y->lchild->parent = x;
    }
    y->lchild = x;

    // 这一步没想出来。由于传的是一级指针x，不能通过指针x直接改变root节点，所以如果x指向根节点则修改root指向为新的根节点
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

// 父节点是y
// 将rbtree_rotate_left中的x和y互换，将lchild和rchild互换
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

// x是插入节点
void rbtree_insert_balance(RBTree* t, RBTreeNode* x) {
    // case 1: x是根节点，变黑
    if (x->parent == t->nil) {
        x->color = BLACK;
        return;
    }
    // case 2: x的父亲是黑色，x保持红色
    if (BLACK == x->parent->color) {
        x->color = RED;
        return;
    }

    // 父节点是红色，有祖父节点（且是黑色）

    RBTreeNode* u = uncle(x);

    /* case 3 
     * 父节点和叔节点都是红色，父辈变黑，祖父节点变红，x保持红色
     * x是红色，父辈和祖父交换颜色，黑高没有变，没有破坏性质5
     * 祖父节点是红色，祖父的父亲可能是红色或nil，为了不破坏性质2和性质4，
     * 将插入节点变为祖父节点，继续走流程
    */
    if (RED == u->color) {
        x->parent->color = BLACK;
        u->color = BLACK;
        x->parent->parent->color = RED;
        x->color = RED;
        x = x->parent->parent;
        rbtree_insert_balance(t, x);
    }
    // 父节点是红色，叔节点是黑色
    else {
        if (x->parent == x->parent->parent->lchild) {
            /* case 4
             * LL型：对祖父节点右旋
             * 将父节点变为黑色，祖父节点变为红色
             * 旋转前通过原祖父节点的路径在旋转后都通过父节点，黑高不变
            */
            if (x == x->parent->lchild) {
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                x->color = RED;
                rbtree_rotate_right(t, x->parent->parent);
            }
            /* case 5
             * LR型：先对父节点左旋再对祖父节点右旋
             * 将插入节点x变为黑色，祖父节点变为红色
             * 旋转前通过原祖父节点的路径在旋转后都通过插入节点x，黑高不变
            */
            else {
                x->parent->parent->color = RED;
                x->color = BLACK;
                rbtree_rotate_left(t, x->parent);
                // 经过旋转x的祖父变成x的父亲
                rbtree_rotate_right(t, x->parent);
            }
        }
        // 记住上面LL，LR型，下面的RR，RL型，只需要将左右孩子互换，左右旋互换即可
        else {
            /* case 6
             * RR型：对祖父节点左旋
             * 将父节点变为黑色，祖父节点变为红色
             * 旋转前通过原祖父节点的路径在旋转后都通过父节点，黑高不变
            */
            if (x == x->parent->rchild) {
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                x->color = RED;
                rbtree_rotate_left(t, x->parent->parent);
            }
            /* case 7
             * RL型：先对父节点右旋再对祖父节点左旋
             * 将插入节点x变为黑色，祖父节点变为红色
             * 旋转前通过原祖父节点的路径在旋转后都通过插入节点x，黑高不变
            */
            else {
                x->parent->parent->color = RED;
                x->color = BLACK;
                rbtree_rotate_right(t, x->parent);
                // 经过旋转x的祖父变成x的父亲
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
    printf("%d %s\n", root->key, root->color == RED ? "红色" : "黑色");
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