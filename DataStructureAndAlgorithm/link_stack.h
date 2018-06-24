#pragma once
#ifndef LinkStack_H
#define LinkStack_H
#include"sequence_stack.h"

template<typename T>
struct LinkStackNode {
	LinkStackNode() : next(nullptr) {}
	T data;
	LinkStackNode *next;
};

template<typename T>
class LinkStack : public StackBase<T> {
public:
	LinkStack() : top(nullptr), len(0) {}
	~LinkStack();
	bool Push(const T &e);
	bool Pop(T &e);
private:
	LinkStackNode<T> *top;
	size_t len;
};

template<typename T>
bool LinkStack<T>::Push(const T & e)
{
	LinkStackNode<T> *s = new LinkStackNode<T>;
	if (!s) {
		return false;
	}
	s->data = e;
	s->next = top;
	top = s;
	++len;
	return true;
}

template<typename T>
bool LinkStack<T>::Pop(T & e)
{
	if (nullptr == top) {
		return false;
	}
	e = top->data;
	LinkStackNode<T> *s = top;
	top = top->next;
	delete s;
	--len;
	return true;
}



#endif // !LinkStack_H
