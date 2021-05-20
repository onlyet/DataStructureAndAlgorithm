#pragma once
#include<assert.h>

template<typename T>
struct LinkNode {
    LinkNode(const T&d) : data(d), next(nullptr) {}
    T data;
    LinkNode *next;
};

template<typename T>
class LinkedList {
public:
    LinkedList();
    LinkedList(T *a, int n);
    ~LinkedList();

//    //在第n个元素前插入，n=0:插入头部
    bool Insert(const T&e, int n);

    bool Delete(int n);

    bool Set(const T& e, int n);

    bool Get(T& e, int n);

//    //这里递归的作用只是找到最后一个结点
//    //不能用p->next= cur,只能用cur->next->next = cur;
    LinkNode<T>* Reverse(LinkNode<T> *cur);

    void createWithLoop(T *a, int n);

    void print();

    // 求倒数第k个结点
    LinkNode<T>* kFromTheBottom(int k);

    LinkNode<T>* reverse();

    bool hasLoop();


private:
//    //n指下标，从0开始
    LinkNode<T>* Locate(int n);

private:
    LinkNode<T> *head = nullptr;
    bool    m_hasLoop = false;
    int     m_nodeNum = 0;
};