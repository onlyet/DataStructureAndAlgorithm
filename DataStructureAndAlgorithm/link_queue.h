#pragma once
#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

template<typename T>
struct LinkQueueNode
{
	LinkQueueNode() : next(nullptr) {}
	T data;
	LinkQueueNode *next;
};

//without head node
template<typename T>
class LinkQueue {
public:
	LinkQueue() : front(nullptr),rear(nullptr) {}
	~LinkQueue();
	bool EnQueue(const T &e);
	bool DeQueue(T &e);
	bool Empty() { return nullptr == front; }
	size_t Length();
	void Clear();
private:
	LinkQueueNode<T> *front;
	LinkQueueNode<T> *rear;
};

template<typename T>
bool LinkQueue<T>::EnQueue(const T & e)
{
	LinkQueueNode<T> *s = new LinkQueueNode<T>;
	if (!s) {
		return false;
	}
	s->data = e;
	if (nullptr != rear) {
		rear->next = s;
	}
	rear = s;
	return true;
}

template<typename T>
bool LinkQueue<T>::DeQueue(T & e)
{
	if (nullptr == front) {
		return false;
	}
	LinkQueueNode<T> *s = front;
	e = front->data;
	front = front->next;
	delete s;
	return true;
}

template<typename T>
size_t LinkQueue<T>::Length()
{
	size_t len = 0;
	LinkQueueNode<T> *p = front;
	while (nullptr != p) {
		++len;
		p = p->next;
	}
	return len;
}

template<typename T>
void LinkQueue<T>::Clear()
{
	LinkQueueNode<T> *p = front, *q;
	while (nullptr != p) {
		q = p->next;
		delete p;
		p = q;
	}
}

#endif // !LINK_QUEUE_H
