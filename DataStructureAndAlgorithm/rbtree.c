
/*
 * 红黑树五个性质：
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
    RBTreeNode* nil;        // 叶子节点
} RBTree;

// 父节点是x
// 需要处理4个节点，x，y，x的父亲，y的左儿子
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
void rbtree_insert_fixup(RBTree* t, RBTreeNode* x) {
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
        rbtree_insert_fixup(t, x);
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
            /* case 4
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
            /* case 5
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

// n是插入节点，y是插入节点的父节点
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
        // 插入的是第一个节点（根节点）
        t->root = n;
    }

    n->parent = y;

    rbtree_insert_fixup(t, n);
}

RBTreeNode* rbtree_find(RBTree* t, KeyType key) {
    RBTreeNode* cur = t->root;
    while (cur != t->nil) {
        if (cur->key > key) {
            cur = cur->lchild;
        }
        else if (cur->key < key) {
            cur = cur->rchild;
        }
        else {
            return cur;
        }
    }
    return NULL;
}

RBTreeNode* rbtree_suffix(RBTree* t, RBTreeNode* n) {
    RBTreeNode* ret = n->rchild;
    RBTreeNode* left = ret->lchild;
    while (left != t->nil) {
        ret = left;
        left = left->lchild;
    }
    return ret;
}

RBTreeNode* rbtree_sibling(RBTreeNode* n) {
    return n == n->parent->lchild ? n->parent->rchild : n->parent->lchild;
}

/*
 * cur是实际删除节点的儿子
 * 旋转要更新兄弟节点
*/
void rbtree_delete_fixup(RBTree* t, RBTreeNode* cur) {
    while (cur != t->root && BLACK == cur->color) {
        RBTreeNode* s = rbtree_sibling(cur);
        if (cur == cur->parent->lchild) {
            /*
             * 情况2 兄弟节点是红色
             * 父节点P改为红色，兄弟节点S改为黑色，对P左旋，兄弟节点变为旋转前的SL
             * 变色旋转后的各路径黑高没有改变
             * 但由于通过N节点的黑高仍少1，继续按后续情况处理
             * 所以兄弟节点如果是红色则转为黑色处理
            */
            if (RED == s->color) {
                cur->parent->color = RED;
                s->color = BLACK;
                rbtree_rotate_left(t, cur->parent);
                s = rbtree_sibling(cur);
            }

            // 以下兄弟节点S是黑色

            /*
             * 情况3 兄弟节点S是黑色，S的两个儿子也是黑色
             * 将S变为红色，通过S的路径黑高减1，此时通过N和通过S的路径的黑高相同，
             * 但是通过P的路径的黑高还是比不通过P的路径的黑高少1，所以还需要继续修复。将当前节点改为父节点P。
             * 注意这里P可能是黑色也可能是红色，这两种情况统一处理了，如果P是红色，则退出循环，将当前节点变为黑色，避免破坏性质4（P,S都是红色）
            */
            if (BLACK == s->lchild->color && BLACK == s->rchild->color) {
                s->color = RED;
                cur = cur->parent;
            }
            else {
                /*
                 * 情况4 兄弟节点S是黑色，S的左儿子SL是红色，S的右儿子SR是黑色
                 * 交换兄弟节点S和左儿子SL的颜色，对S右旋。
                 * 旋转和变色后各路径的黑高和原来相同，通过N的路径还是黑高少1，通过SR的路径黑高不变，此时满足情况5，跳到情况5处理。
                */
                if (RED == s->lchild->color && BLACK == s->rchild->color) {
                    s->color = RED;
                    s->lchild->color = BLACK;
                    rbtree_rotate_right(t, s);
                    s = rbtree_sibling(cur);
                }

                /*
                 * 情况5 兄弟节点S是黑色，S的右儿子SR是红色
                 * 父节点P和兄弟节点S互换颜色，右儿子SR变为黑色，然后对P左旋
                 * 修复后，原来通过N节点的路径多了个黑色节点P，黑高加1；
                 * 原来通过SL的路径黑高不变（P->S->SL变为S->P->SL，而SL在旋转后变为新兄弟）；
                 * 原来通过SR的路径黑高也不变（P->S->SR变为S->SR，少了个红节点不影响，而SR在旋转后变为N的叔父）
                 * 此时性质5已修复。
                */
                if (RED == s->rchild->color) {
                    s->color = cur->parent->color;
                    cur->parent->color = BLACK;
                    s->rchild->color = BLACK;
                    rbtree_rotate_left(t, cur->parent);

                    // 红黑树已修复，退出循环
                    cur = t->root;
                }
            }
        }
        // 与上面是镜像，互换左右孩子和左右旋即可
        else {
            if (RED == s->color) {
                cur->parent->color = RED;
                s->color = BLACK;
                rbtree_rotate_right(t, cur->parent);
                s = rbtree_sibling(cur);
            }

            if (BLACK == s->lchild->color && BLACK == s->rchild->color) {
                s->color = RED;
                cur = cur->parent;
            }
            else {
                if (RED == s->rchild->color && BLACK == s->lchild->color) {
                    s->color = RED;
                    s->rchild->color = BLACK;
                    rbtree_rotate_left(t, s);
                    s = rbtree_sibling(cur);
                }

                if (RED == s->lchild->color) {
                    s->color = cur->parent->color;
                    cur->parent->color = BLACK;
                    s->lchild->color = BLACK;
                    rbtree_rotate_right(t, cur->parent);

                    cur = t->root;
                }
            }
        }
    }
    /* 
     * 实际删除节点是黑色，儿子节点是红色时会走到这
     * 情况1会走到这
     * 如果当前节点是根节点或者是红色，则将颜色改为黑色
    */ 
    cur->color = BLACK;
}

/*
 * d是想要删除节点
 * r是实际删除的节点（d或者d的后继节点）
 * cur是实际删除节点的儿子（当前节点）

 * 返回实际删除的节点，在外部free
*/
RBTreeNode* rbtree_delete(RBTree* t, RBTreeNode* d) {
    RBTreeNode* r;
    RBTreeNode* cur;
    // 有两个非叶子节点则查找后继节点
    if (d->lchild != t->nil && d->rchild != t->nil) {
        r = rbtree_suffix(t, d);
    }
    else {
        r = d;
    }

    if (r->lchild != t->nil) {
        cur = r->lchild;
    }
    else {
        cur = r->rchild;
    }

    // 实际删除的节点r替换为它的儿子n
    if (r->parent == t->nil) {
        t->root = cur;
    }
    else if (r == r->parent->lchild) {
        r->parent->lchild = cur;
    }
    else {
        r->parent->rchild = cur;
    }
    cur->parent = r->parent;
    
    // 想要删除的节点不用实际删除，替换key，value就行
    if (r != d) {
        d->key = r->key;
        d->value = r->value;
    }
    
    if (BLACK == r->color) {
        rbtree_delete_fixup(t, cur);
    }
    return r;
}

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

    KeyType a[] = { 11, 32, 23, 54, 15, 66, 44, 99, 100, 8 };

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

    printf("插入后：\n");
    print(&t, t.root);
    printf("\n");

    //printf("删除前：\n");
    for (i = 0; i < len /*/ 2*/; ++i) {
        RBTreeNode* n = rbtree_find(&t, a[i]);
        if (n) {
            printf("删除%d\n", a[i]);
            RBTreeNode* d = rbtree_delete(&t, n);
            if (d) {
                free(d);
            }
            print(&t, t.root);
            printf("\n");
        }
    }
    printf("删除后：\n");
    print(&t, t.root);

    free(t.nil);
    t.nil = NULL;

    system("pause");
    return 0;
}