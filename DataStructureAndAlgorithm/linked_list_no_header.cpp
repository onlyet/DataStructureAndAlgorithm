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
LinkNode<T>* LinkedList<T>::getHead()
{
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
void LinkedList<T>::createWithLoop(T *a, int n, int loopEntry) {
    
    if (!a || n < 1) {
        return;
    }
    head = new LinkNode<T>(a[0]);
    LinkNode<T> *cur = nullptr;
    LinkNode<T> *loopNode = nullptr;
    for (int i = 0; i < n; ++i) {
        if (0 == i) {
            cur = head;
        }
        else {
            cur->next = new LinkNode<T>(a[i]);
            cout << cur->data << " ";
            cur = cur->next;
        }
        if (loopEntry == i) {
            loopNode = cur;
        }
    }
    cout << cur->data << endl;
    cur->next = loopNode;

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
LinkNode<T>* LinkedList<T>::loopMeetPoint() {
    LinkNode<T> *fast = head, *slow = head;
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) {
            return fast;
        }
    }
    return nullptr;
}

template<typename T>
LinkNode<T>* LinkedList<T>::loopEntryPoint(LinkNode<T>* meetPoint)
{
    LinkNode<T> *p = head, *q = meetPoint;
    //auto p = head, q = meetPoint;
    while (p != q) {
        p = p->next;
        q = q->next;
    }
    return p;
}


template<typename T>
void createTwoIntersectingList(LinkedList<T>& l, LinkedList<T>& r)
{
    int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
    int b[2] = { 22, 33 };

    LinkNode<T> *p = nullptr, *q = nullptr;
    for (int i = 0; i < 5; ++i) {
        if (0 == i) {
            l.head = new LinkNode<T>(a[i]);
            p = l.head;
        }
        else {
            p->next = new LinkNode<T>(a[i]);
            p = p->next;
        }
    }
    for (int i = 0; i < 2; ++i) {
        if (0 == i) {
            r.head = new LinkNode<T>(b[i]);
            q = r.head;
        }
        else {
            q->next = new LinkNode<T>(b[i]);
            q = q->next;
        }
    }
    q->next = p;

    for (int i = 5; i < 10; ++i) {
        p->next = new LinkNode<T>(a[i]);
        p = p->next;
    }
}

template<typename T>
LinkNode<T>* getIntersection(LinkedList<T>& l, LinkedList<T>& r)
{
    LinkNode<T>* p = l.getHead();
    LinkNode<T>* q = r.getHead();
    if (!p || !q) {
        return nullptr;
    }
    int llen = 1, rlen = 1;
    while (p->next) {
        ++llen;
        p = p->next;
    }
    while (q->next) {
        ++rlen;
        q = q->next;
    }
    // 注意：最后一个结点不同，则肯定不相交
    if (p != q) {
        return nullptr;
    }

    p = l.getHead();
    q = r.getHead();
    int s;
    if (llen > rlen) {
        s = llen - rlen;
        while (p && s > 0) {
            p = p->next;
            --s;
        }
    }
    else {
        s = rlen - llen;
        while (q && s > 0) {
            q = q->next;
            --s;
        }
    }
    while (p && q) {
        if (p == q) {
            return p;
        }
        p = p->next;
        q = q->next;
    }
    return nullptr;
}
