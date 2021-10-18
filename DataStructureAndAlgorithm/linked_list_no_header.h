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
    template<typename U>
    friend void createTwoIntersectingList(LinkedList<U>& l, LinkedList<U>& r);

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

    // 获取头结点
    LinkNode<T>* getHead();

    void createWithLoop(T *a, int n, int loopEntry);

    void print();

    // 求倒数第k个结点
    LinkNode<T>* kFromTheBottom(int k);

    LinkNode<T>* reverse();

    // 如果有环，则返回相遇点
    LinkNode<T>* loopMeetPoint();

    // 返回带环单链表的入口点
    LinkNode<T>* loopEntryPoint(LinkNode<T>* meetPoint);

private:
//    //n指下标，从0开始
    LinkNode<T>* Locate(int n);

private:
    LinkNode<T> *head = nullptr;
    bool    m_hasLoop = false;
    int     m_nodeNum = 0;
};


template<typename T>
void createTwoIntersectingList(LinkedList<T>& l, LinkedList<T>& r);

// 获取两无环单链表的相交点，前提是两个链表都无环，否则死循环
template<typename T>
LinkNode<T>* getIntersection(LinkedList<T>& l, LinkedList<T>& r);
