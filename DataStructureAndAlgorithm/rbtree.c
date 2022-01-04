
/*
 * �����������ʣ�
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
    RBTreeNode* nil;        // Ҷ�ӽڵ�
} RBTree;

// ���ڵ���x
// ��Ҫ����4���ڵ㣬x��y��x�ĸ��ף�y�������
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
void rbtree_insert_fixup(RBTree* t, RBTreeNode* x) {
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
        rbtree_insert_fixup(t, x);
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
            /* case 4
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
            /* case 5
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

// n�ǲ���ڵ㣬y�ǲ���ڵ�ĸ��ڵ�
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
        // ������ǵ�һ���ڵ㣨���ڵ㣩
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
 * cur��ʵ��ɾ���ڵ�Ķ���
 * ��תҪ�����ֵܽڵ�
*/
void rbtree_delete_fixup(RBTree* t, RBTreeNode* cur) {
    while (cur != t->root && BLACK == cur->color) {
        RBTreeNode* s = rbtree_sibling(cur);
        if (cur == cur->parent->lchild) {
            /*
             * ���2 �ֵܽڵ��Ǻ�ɫ
             * ���ڵ�P��Ϊ��ɫ���ֵܽڵ�S��Ϊ��ɫ����P�������ֵܽڵ��Ϊ��תǰ��SL
             * ��ɫ��ת��ĸ�·���ڸ�û�иı�
             * ������ͨ��N�ڵ�ĺڸ�����1�������������������
             * �����ֵܽڵ�����Ǻ�ɫ��תΪ��ɫ����
            */
            if (RED == s->color) {
                cur->parent->color = RED;
                s->color = BLACK;
                rbtree_rotate_left(t, cur->parent);
                s = rbtree_sibling(cur);
            }

            // �����ֵܽڵ�S�Ǻ�ɫ

            /*
             * ���3 �ֵܽڵ�S�Ǻ�ɫ��S����������Ҳ�Ǻ�ɫ
             * ��S��Ϊ��ɫ��ͨ��S��·���ڸ߼�1����ʱͨ��N��ͨ��S��·���ĺڸ���ͬ��
             * ����ͨ��P��·���ĺڸ߻��ǱȲ�ͨ��P��·���ĺڸ���1�����Ի���Ҫ�����޸�������ǰ�ڵ��Ϊ���ڵ�P��
             * ע������P�����Ǻ�ɫҲ�����Ǻ�ɫ�����������ͳһ�����ˣ����P�Ǻ�ɫ�����˳�ѭ��������ǰ�ڵ��Ϊ��ɫ�������ƻ�����4��P,S���Ǻ�ɫ��
            */
            if (BLACK == s->lchild->color && BLACK == s->rchild->color) {
                s->color = RED;
                cur = cur->parent;
            }
            else {
                /*
                 * ���4 �ֵܽڵ�S�Ǻ�ɫ��S�������SL�Ǻ�ɫ��S���Ҷ���SR�Ǻ�ɫ
                 * �����ֵܽڵ�S�������SL����ɫ����S������
                 * ��ת�ͱ�ɫ���·���ĺڸߺ�ԭ����ͬ��ͨ��N��·�����Ǻڸ���1��ͨ��SR��·���ڸ߲��䣬��ʱ�������5���������5����
                */
                if (RED == s->lchild->color && BLACK == s->rchild->color) {
                    s->color = RED;
                    s->lchild->color = BLACK;
                    rbtree_rotate_right(t, s);
                    s = rbtree_sibling(cur);
                }

                /*
                 * ���5 �ֵܽڵ�S�Ǻ�ɫ��S���Ҷ���SR�Ǻ�ɫ
                 * ���ڵ�P���ֵܽڵ�S������ɫ���Ҷ���SR��Ϊ��ɫ��Ȼ���P����
                 * �޸���ԭ��ͨ��N�ڵ��·�����˸���ɫ�ڵ�P���ڸ߼�1��
                 * ԭ��ͨ��SL��·���ڸ߲��䣨P->S->SL��ΪS->P->SL����SL����ת���Ϊ���ֵܣ���
                 * ԭ��ͨ��SR��·���ڸ�Ҳ���䣨P->S->SR��ΪS->SR�����˸���ڵ㲻Ӱ�죬��SR����ת���ΪN���常��
                 * ��ʱ����5���޸���
                */
                if (RED == s->rchild->color) {
                    s->color = cur->parent->color;
                    cur->parent->color = BLACK;
                    s->rchild->color = BLACK;
                    rbtree_rotate_left(t, cur->parent);

                    // ��������޸����˳�ѭ��
                    cur = t->root;
                }
            }
        }
        // �������Ǿ��񣬻������Һ��Ӻ�����������
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
     * ʵ��ɾ���ڵ��Ǻ�ɫ�����ӽڵ��Ǻ�ɫʱ���ߵ���
     * ���1���ߵ���
     * �����ǰ�ڵ��Ǹ��ڵ�����Ǻ�ɫ������ɫ��Ϊ��ɫ
    */ 
    cur->color = BLACK;
}

/*
 * d����Ҫɾ���ڵ�
 * r��ʵ��ɾ���Ľڵ㣨d����d�ĺ�̽ڵ㣩
 * cur��ʵ��ɾ���ڵ�Ķ��ӣ���ǰ�ڵ㣩

 * ����ʵ��ɾ���Ľڵ㣬���ⲿfree
*/
RBTreeNode* rbtree_delete(RBTree* t, RBTreeNode* d) {
    RBTreeNode* r;
    RBTreeNode* cur;
    // ��������Ҷ�ӽڵ�����Һ�̽ڵ�
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

    // ʵ��ɾ���Ľڵ�r�滻Ϊ���Ķ���n
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
    
    // ��Ҫɾ���Ľڵ㲻��ʵ��ɾ�����滻key��value����
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

    printf("�����\n");
    print(&t, t.root);
    printf("\n");

    //printf("ɾ��ǰ��\n");
    for (i = 0; i < len /*/ 2*/; ++i) {
        RBTreeNode* n = rbtree_find(&t, a[i]);
        if (n) {
            printf("ɾ��%d\n", a[i]);
            RBTreeNode* d = rbtree_delete(&t, n);
            if (d) {
                free(d);
            }
            print(&t, t.root);
            printf("\n");
        }
    }
    printf("ɾ����\n");
    print(&t, t.root);

    free(t.nil);
    t.nil = NULL;

    system("pause");
    return 0;
}