#include "linked_list_no_header.h"

template<typename T>
LinkedList<T>::LinkedList() {

}


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
    if (m_hasLoop) {
        LinkNode<T>* p = head;
        for (int i = 0; i < m_nodeNum; ++i) {
            head = head->next;
            delete p;
            p = head;
        }
        head = nullptr;
        return;
    }

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

template<typename T>
void LinkedList<T>::createWithLoop(T *a, int n) {
    
    head = new LinkNode<T>(a[0]);
    LinkNode<T> *cur = head;
    for (int i = 1; i < n; ++i) {
        cur->next = new LinkNode<T>(a[i]);
        cout << cur->data << " ";
        cur = cur->next;
    }
    cur->next = head;
    cout << cur->data << endl;

    m_hasLoop = true;
    m_nodeNum = n;
}

template<typename T>
void LinkedList<T>::print() {
    LinkNode<T>* p = head;
    while (p) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

template<typename T>
LinkNode<T>* LinkedList<T>::kFromTheBottom(int k) {
    if (!head) {
        return nullptr;
    }
    LinkNode<T> *p = head;
    LinkNode<T> *q = p;
    for (int i = 0; q && i < k - 1; ++i) {
        q = q->next;
    }
    while (q && q->next) {
        p = p->next;
        q = q->next;
    }
    return p;
}

template<typename T>
LinkNode<T>* LinkedList<T>::reverse() {
    LinkNode<T>* prev = nullptr;
    LinkNode<T>* cur = head;
    LinkNode<T>* next;
    while (cur) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    head = prev;
    return head;
}

template<typename T>
bool LinkedList<T>::hasLoop() {
    LinkNode<T> *fast = head, *slow = head;
    while (/*fast && slow*/fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) {
            return true;
        }
    }
    return false;
}
