#include "linked_list_no_header.h"

template<typename T>
LinkedList<T>::LinkedList(T *a, int n)
{
    assert(a != nullptr && n > 0);
    head = new LinkNode<T>(a[0]);
    LinkNode<T> *cur = head;
    for (int i = 1; i < n; ++i) {
        cur->next = new LinkNode<T>(a[i]);
        cur = cur->next;
    }
}

template<typename T>
LinkedList<T>::~LinkedList()
{
    while (head) {
        LinkNode<T> *p = head;
        head = head->next;
        delete p;
    }
}


//在第n个元素前插入，n=0:插入头部
template<typename T>
bool LinkedList<T>::Insert(const T&e, int n)
{
    if (n == 0) {
        LinkNode<T> *s = new LinkNode<T>(e);
        s->next = head;
        head = s;
    }
    LinkNode<T> *p = Locate(n - 1);
    if (!p) {
        return false;
    }
    LinkNode<T> *s = new LinkNode<T>(e);
    s->next = p->next;
    p->next = s;
    return true;
}

template<typename T>
bool LinkedList<T>::Delete(int n)
{
    if (!head) {
        return false;
    }
    LinkNode<T> *p, *q;
    if (n == 0) {
        p = head;
        head = head->next;
        delete p;
    }
    p = Locate(n - 1);
    if (!p) {
        return false;
    }
    q = p->next;
    p->next = q->next;
    delete q;
    return true;
}

template<typename T>
bool LinkedList<T>::Set(const T& e, int n)
{
    LinkNode<T> *p = Locate(n);
    if (!p) {
        return false;
    }
    p->data = e;
    return true;
}

template<typename T>
bool LinkedList<T>::Get(T& e, int n)
{
    LinkNode<T> *p = Locate(n);
    if (!p) {
        return false;
    }
    e = p->data;
    return true;
}

template<typename T>
LinkNode<T>* LinkedList<T>::Reverse(LinkNode<T> *cur)
{
    if (!cur || !cur->next) {
        return cur;
    }
    LinkNode<T> *p = Reverse(cur->next);
    if (!p->next) {
        head = p;
    }
    cur->next->next = cur;  //不能使用p，因为p永远指向翻转后的头结点
    cur->next = nullptr;
    return head;
}

template<typename T>
LinkNode<T>* LinkedList<T>::Locate(int n)
{
    if (n < 0) {
        return nullptr;
    }
    int i = 0;
    LinkNode<T> *p = head;
    while (p && i <= n) {
        p = p->next;
        ++i;
    }
    return p;
}