/*
 * m��B��
 * M��Ϊ���������������������������ָ����һ�����ӵ�����Ķ�������
 * ���壺
 * 1. ÿ���ڵ����m���ӽڵ�
 * 2. ����ڲ��ڵ���ӽڵ�������k, �� m/2 < k < m
 * 3. ���ڵ��������Ҷ�ӽڵ㣬�������������ӽڵ�
 * 4. ��k���ӽڵ�Ľڵ���k-1���ؼ��֣��ؼ��ֵ�������
 * 5. Ҷ�ӽڵ㶼��ͬһ��
*/

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define HalfDegree 3                // ������һ��

typedef int KeyType;

typedef struct _btree_node {
    int key_num;				    // �ؼ�������
    KeyType* keys;	                // �ؼ�������
    struct _btree_node** childs;    // �ӽڵ�����
    int is_leaf;				    // �Ƿ�Ҷ�ӽڵ㣬1��Ҷ�ӣ�0����
} btree_node;

typedef struct _btree {
    btree_node* root;
    int         half_degree;         // ������һ��
} btree;

/*
 * �����ڵ�
 * half_degree ������һ��
 * is_leaf �Ƿ�Ҷ�ӽڵ�
 * ���ش����Ľڵ�
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
 * ���ѽڵ�
 * B��t��x�ڵ�ĵ�i���ӽڵ���Ҫ����
*/
void btree_split_node(btree* t, btree_node* x, int i) {
    // y��x�ĵ�i������
    btree_node* y = x->childs[i];
    // z�������ڵ�
    btree_node* z = btree_create_node(t->half_degree, y->is_leaf);
    
    int j;
    // �����ѽڵ�x�ĺ�һ��ؼ��ֿ����������ڵ�
    for (j = 0; j < t->half_degree - 1; ++j) {
        z->keys[j] = y->keys[j + t->half_degree];
    }
    // �����ѽڵ�x�ĺ�һ���ӽڵ�ָ�뿽���������ڵ�
    if (!y->is_leaf) {
        for (j = 0; j < t->half_degree; ++j) {
            z->childs[j] = y->childs[j + t->half_degree];
        }
    }

    y->key_num = t->half_degree;
    z->key_num = t->half_degree;

    // x�ڵ�ĵ�i���ؼ��ֿ�ʼ֮������йؼ��ֺ��ƣ����һ���ڵ㲻��Ҫ���ƣ��������������� [i,key_num-1)
    for (j = x->key_num - 1; j > i; --j) {
        x->keys[j] = x->keys[j - 1];
    }
    x->keys[i] = y->keys[t->half_degree - 1];

    // x�ڵ�ĵ�i+1���ӽڵ㿪ʼ֮��������ӽڵ���ƣ����һ���ڵ㲻��Ҫ���ƣ��������������� [i+1,key_num-1)
    for (j = x->key_num - 1; j > i + 1; --j) {
        x->childs[j] = x->childs[j - 1];
    }
    // i or i+1 ?
    x->childs[i + 1] = z;

    ++x->key_num;
}

/*
 * ��B���ĵ�x�ڵ�����key
 * key�ǲ���ļ�
*/
void btree_insert_nonfull(btree* t, btree_node* x, KeyType key) {
    // Ҷ�ӽڵ㲻��Ҫ�����ӽڵ�ָ��
    int i;
    int j;
    if (x->is_leaf) {
        // ���ҵ�����λ��
        for (i = 0; i <= x->key_num - 1 && key > x->keys[i]; ) {
            ++i;
        }
        // ����ڵ��Ƿ����ģ����Է������һ��key֮����Ǹ�key�����з���keys[key_num]û����
        for (j = x->key_num ; j > i; --j) {
            x->keys[j] = x->keys[j - 1];
        }
        x->keys[i] = key;
    }
    else {
        // btree_insert_nonfullӦ�����������жϽڵ��Ƿ�����
        // ���ҵ���������λ��i
        for (i = 0; i <= x->key_num - 1 && key > x->keys[i]; ) {
            ++i;
        }

        if (x->childs[i]->key_num == 2 * t->half_degree - 1) {
            btree_split_node(t, x, i);

            // �Ƚ�key��x�ڵ�ĵ�i��key�����key��������i���ӽڵ㣬keyС������i+1���ӽڵ�
            if (key > x->keys[i]) {
                ++i;
            }
        }

        // ��������
        btree_insert_nonfull(t, x->childs[i], key);
    }
}

/*
 * key�ǲ���ļ�
*/
void btree_insert(btree* t, KeyType key) {
    int max_key_num = 2 * t->half_degree - 1;
    btree_node* root = t->root;
    if (root->key_num == max_key_num) {
        // �����µĸ��ڵ�
        btree_node* new_root = btree_create_node(t->half_degree, 0);
        new_root->childs[0] = root;
        new_root->keys[0] = root->keys[t->half_degree - 1];
        ++new_root->key_num;

        // ���Ѿɵĸ��ڵ�
        btree_split_node(t, new_root, 0);

        // �Ƚ�key�;ɸ��ڵ���м�ֵ�����key��������1���ӽڵ㣬keyС������0���ӽڵ�
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