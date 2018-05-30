#pragma once
#ifndef SEQUENCE_STACK_H
#define SEQUENCE_STACK_H

template<typename T>
class StackBase {
public:
	virtual ~StackBase() {}

	virtual void Clear() = 0;
	virtual bool Empty() = 0;
	virtual bool GetTop(T &e) = 0;
	virtual bool SetTop(const T &e) = 0;
	virtual bool Push(const T &e) = 0;
	virtual bool Pop(T &e) = 0;
	virtual size_t Length() = 0;
	virtual void Print() = 0;
};
#endif // !SEQUENCE_STACK_H

template<typename T>
class SeqStack : public StackBase<T>{
public:
	SeqStack() : data(new T[STACK_INIT_SIZE]), top(-1), stack_size(STACK_INIT_SIZE) {}
	~SeqStack() { delete[] data; }
	void Clear() override;
	bool Empty() override { return -1 == top; }
	bool GetTop(T &e) override;
	bool SetTop(const T &e) override;
	bool Push(const T &e) override;
	bool Pop(T &e) override;
	size_t Length() override { return top + 1; }
	void Print() override;
public:
	static const size_t STACK_INIT_SIZE = 100;
	static const size_t STACK_INCREMENT_SIZE = 10;
private:
	T *data;
	int top;	//pointer to top of Stack
	size_t stack_size; //current allocated size
};

template<typename T>
bool SeqStack<T>::Push(const T & e)
{
	if (stack_size - 1 == top) {
		T *tmp = new T[(STACK_INCREMENT_SIZE + stack_size) * sizeof(T)];
		memcpy(tmp, data, stack_size * sizeof(T));
		delete[] data;
		data = tmp;
		stack_size += STACK_INCREMENT_SIZE;
	}
	data[++top] = e;
	return true;
}

template<typename T>
bool SeqStack<T>::Pop(T & e)
{
	if (-1 == top) {
		return false;
	}
	e = data[top--];
	return true;
}

template<typename T>
void SeqStack<T>::Clear()
{
	delete data;
	data = new T[STACK_INCREMENT_SIZE * sizeof(T)];
	top = -1;
}

template<typename T>
bool SeqStack<T>::GetTop(T & e)
{
	if (-1 == top) {
		return false;
	}
	e = data[top];
}

template<typename T>
bool SeqStack<T>::SetTop(const T & e)
{
	if (-1 == top) {
		return false;
	}
	data[top] = e;
}

template<typename T>
void SeqStack<T>::Print()
{
	cout << "Print all elements:" << endl;
	for (int i = 0; i <= top; ++i) {
		cout << data[i] << " ";
	}
	cout << endl;
}
