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
    LinkedList(T *a, int n);
//    {
//        assert(a != nullptr && n > 0);
//        head = new LinkNode<T>(a[0]);
//        for (int i = 1; i < n; ++i) {
//            head->next = new T(a[i]);
//        }
//    }
//
    ~LinkedList();
//    {
//        while (head) {
//            LinkNode<T> *p = head;
//            head = head->next;
//            delete p;
//        }
//    }
//    
//    //在第n个元素前插入，n=0:插入头部
    bool Insert(const T&e, int n);
//    {
//        if (n == 0) {
//            LinkNode<T> *s = new LinkNode<T>(e);
//            s->next = head;
//            head = s;
//        }
//        LinkNode<T> *p = Locate(n - 1);
//        if (!p) {
//            return false;
//        }
//        LinkNode<T> *s = new LinkNode<T>(e);
//        s->next = p->next;
//        p->next = s;
//        return true;
//    }
//
    bool Delete(int n);
//    {
//        if (!head) {
//            return false;
//        }
//        LinkNode<T> *p, *q;
//        if (n == 0) {
//            p = head;
//            head = head->next;
//            delete p;
//        }
//        p = Locate(n - 1);
//        if (!p) {
//            return false;
//        }
//        q = p->next;
//        p->next = q->next;
//        delete q;
//        return true;
//    }
//
    bool Set(const T& e, int n);
//    {
//        LinkNode<T> *p = Locate(n);
//        if (!p) {
//            return false;
//        }
//        p->data = e;
//        return true;
//    }
//
    bool Get(T& e, int n);
//    {
//        LinkNode<T> *p = Locate(n);
//        if (!p) {
//            return false;
//        }
//        e = p->data;
//        return true;
//    }
//
//    //这里递归的作用只是找到最后一个结点
//    //不能用p->next= cur,只能用cur->next->next = cur;
    LinkNode<T>* Reverse(LinkNode<T> *cur);
//    {
//        if (!cur || !cur->next) {
//            return cur;
//        }
//        LinkNode<T> *p = Reverse(cur->next);
//        if (!p->next) {
//            head = p;
//        }
//        cur->next->next = cur;  //不能使用p，因为p永远指向翻转后的头结点
//        cur->next = nullptr;
//        return head;
//    }
//
private:
//    //n指下标，从0开始
    LinkNode<T>* Locate(int n);
//    {
//        if (n < 0) {
//            return nullptr;
//        }
//        int i = 0;
//        LinkNode<T> *p = head;
//        while (p && i <= n) {
//            p = p->next;
//            ++i;
//        }
//        return p;
//    }

private:
    LinkNode<T> *head = nullptr;
};