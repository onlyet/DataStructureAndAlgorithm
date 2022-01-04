/*
 * m阶B树
 * M称为阶数或度数或叉数或最多子树数，指的是一个结点拥有最多的儿子数。
 * 定义：
 * 1. 每个节点最多m个子节点
 * 2. 如果内部节点的子节点数量是k, 则 m/2 < k < m
 * 3. 根节点如果不是叶子节点，则至少有两个子节点
 * 4. 有k个子节点的节点有k-1个关键字，关键字递增排序
 * 5. 叶子节点都在同一层
*/

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define HalfDegree 3                // 阶数的一半

typedef int KeyType;

typedef struct _btree_node {
    int key_num;				    // 关键字数量
    KeyType* keys;	                // 关键字数组
    struct _btree_node** childs;    // 子节点数组
    int is_leaf;				    // 是否叶子节点，1是叶子，0不是
} btree_node;

typedef struct _btree {
    btree_node* root;
    int         half_degree;         // 阶数的一半
} btree;

/*
 * 创建节点
 * half_degree 阶树的一半
 * is_leaf 是否叶子节点
 * 返回创建的节点
*/
btree_node* btree_create_node(int half_degree, int is_leaf) {

    btree_node* n = (btree_node*)calloc(1, sizeof(btree_node));
    assert(NULL != n);

    n->keys = (KeyType*)calloc(1, sizeof(KeyType) * (2 * half_degree - 1));
    assert(NULL != n->keys);

    n->childs = (btree_node**)calloc(1, sizeof(btree_node*) * (2 * half_degree));
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

void btree_create(btree* t, int half_degree) {
    t->root = btree_create_node(half_degree, 1);
    t->half_degree = half_degree;
}

/*
 * 分裂节点
 * B树t的x节点的第i个子节点需要分裂
*/
void btree_split_node(btree* t, btree_node* x, int i) {
    // y是x的第i个孩子
    btree_node* y = x->childs[i];
    // z是新增节点
    btree_node* z = btree_create_node(t->half_degree, y->is_leaf);
    
    int j;
    // 将分裂节点x的后一半关键字拷贝到新增节点
    for (j = 0; j < t->half_degree - 1; ++j) {
        z->keys[j] = y->keys[j + t->half_degree];
    }
    // 将分裂节点x的后一半子节点指针拷贝到新增节点
    if (!y->is_leaf) {
        for (j = 0; j < t->half_degree; ++j) {
            z->childs[j] = y->childs[j + t->half_degree];
        }
    }

    y->key_num = t->half_degree;
    z->key_num = t->half_degree;

    // x节点的第i个关键字开始之后的所有关键字后移，最后一个节点不需要后移，不会出现这种情况 [i,key_num-1)
    for (j = x->key_num - 1; j > i; --j) {
        x->keys[j] = x->keys[j - 1];
    }
    x->keys[i] = y->keys[t->half_degree - 1];

    // x节点的第i+1个子节点开始之后的所有子节点后移，最后一个节点不需要后移，不会出现这种情况 [i+1,key_num-1)
    for (j = x->key_num - 1; j > i + 1; --j) {
        x->childs[j] = x->childs[j - 1];
    }
    // i or i+1 ?
    x->childs[i + 1] = z;

    ++x->key_num;
}

/*
 * 向B树的的x节点插入键key
 * key是插入的键
*/
void btree_insert_nonfull(btree* t, btree_node* x, KeyType key) {
    // 叶子节点不需要处理子节点指针
    int i;
    int j;
    if (x->is_leaf) {
        // 先找到插入位置
        for (i = 0; i <= x->key_num - 1 && key > x->keys[i]; ) {
            ++i;
        }
        // 这里节点是非满的，可以访问最后一个key之后的那个key，所有访问keys[key_num]没问题
        for (j = x->key_num ; j > i; --j) {
            x->keys[j] = x->keys[j - 1];
        }
        x->keys[i] = key;
    }
    else {
        // btree_insert_nonfull应该是在这里判断节点是否满了
        // 先找到插入子树位置i
        for (i = 0; i <= x->key_num - 1 && key > x->keys[i]; ) {
            ++i;
        }

        if (x->childs[i]->key_num == 2 * t->half_degree - 1) {
            btree_split_node(t, x, i);

            // 比较key和x节点的第i个key，如果key大则插入第i个子节点，key小则插入第i+1个子节点
            if (key > x->keys[i]) {
                ++i;
            }
        }

        // 插入子树
        btree_insert_nonfull(t, x->childs[i], key);
    }
}

/*
 * key是插入的键
*/
void btree_insert(btree* t, KeyType key) {
    int max_key_num = 2 * t->half_degree - 1;
    btree_node* root = t->root;
    if (root->key_num == max_key_num) {
        // 创建新的根节点
        btree_node* new_root = btree_create_node(t->half_degree, 0);
        new_root->childs[0] = root;
        new_root->keys[0] = root->keys[t->half_degree - 1];
        ++new_root->key_num;

        // 分裂旧的根节点
        btree_split_node(t, new_root, 0);

        // 比较key和旧根节点的中间值，如果key大则插入第1个子节点，key小则插入第0个子节点
        int i = 0;
        if (key > new_root->keys[i]) {
            ++i;
        }
        btree_insert_nonfull(t, new_root->childs[i], key);
    }
    else {
        btree_insert_nonfull(t, root, key);
    }
}

int main() {
    btree t;

    btree_create(&t, HalfDegree);
}