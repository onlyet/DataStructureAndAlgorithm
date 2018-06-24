#pragma once
#ifndef CIRCULAR_SEQUENCE_QUEUE_H
#define CIRCULAR_SEQUENCE_QUEUE_H


template<typename T>
class CircularSeqQueue {
public:
	CircularSeqQueue() : data(new T[QueueInitSize]), front(0), rear(0), queue_size(QueueInitSize) {}
	~CircularSeqQueue() { delete[] data; data(nullptr); front = rear = queue_size = 0; }
	bool EnQueue(const T &e);
	bool DeQueue(T &e);
	size_t Length() { return (rear - front + queue_size) % queue_size; }
	bool Empty() { return rear == front; }
	void Clear() { front = rear = 0; }
	T *GetHead() { if (Empty()) { return nullptr; } return data[front]; }
public:
	static const QueueInitSize = 100;
	static const QueueIncrementSize = 10;
private:
	T *data;
	int front;
	int rear;
	int queue_size;
};

template<typename T>
bool CircularSeqQueue<T>::EnQueue(const T & e)
{
	if ((rear + 1) % queue_size == front) {
		T *new_data = new T[(queue_size + QueueIncrementSize) * sizeof(T)];
		memcpy(new_data, data, queue_size * sizeof(T));
		delete[] data;
		data = new_data;
		queue_size += QueueIncrementSize;
	}
	data[rear] = e;
	//if ((queue_size - 1) == rear) {
	//	rear = 0;
	//}
	//else {
	//	++rear;
	//}
	rear = (rear + 1) % queue_size;
	return true;
}

template<typename T>
bool CircularSeqQueue<T>::DeQueue(T & e)
{
	if (front == rear) {
		return false;
	}
	e = data[front];
	front = (front + 1) % queue_size;
	retrun true;
}



#endif // !CURCULAR_SEQUENCE_QUEUE_H
