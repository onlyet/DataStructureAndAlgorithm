#pragma once
#ifndef STACK_QUEUE_INTERVIEW_H
#define STACK_QUEUE_INTERVIEW_H
#include<stack>
#include<queue>
#include<time.h>

template<typename T>
class Stack {
public:
	void Push(const T &e);
	void Pop();
	T Min();	//return minimal value of the stack, time complexity: O(1)
private:
	std::stack<T> s_data;
	std::stack<T> s_min_elem;
};

template<typename T>
void Stack<T>::Push(const T &e)
{
	if (s_min_elem.empty() || e < s_min_elem.top())
		s_min_elem.push(e);
	s_data.push(e);
}

template<typename T>
void Stack<T>::Pop()
{
	assert(!s_data.empty());
	if (s_data.top() == s_min_elem.top())
		s_min_elem.pop();
	s.pop();
}

template<typename T>
T Stack<T>::Min()
{
	return s_min_elem.top();
}

//Achieve a queue using two stack
//if q_out is empty, pop elements of q_in and push into q_out
//then directly pop the top element of q_out
template<typename T>
class QueueWithTwoStack {
public:
	void Push(const T &e) 
	{
		s_in.push(e);
	}
	void Pop()
	{
		assert(!s_in.empty() || !s_out.empty());
		if (s_out.empty()) {
			while (!s_in.empty()) {
				s_out.push(s_in.top());
				s_in.pop();
			}
		}
		s_out.pop();
	}
	const T& Front()
	{
		assert(!s_in.empty() || !s_out.empty());
		if (s_out.empty()) {
			while (!s_in.empty()) {
				s_out.push(s_in.top());
				s_in.pop();
			}
		}
		return s_out.top();
	}
private:
	std::stack<T> s_in;		//to EnQueue
	std::stack<T> s_out;	//to DeQueue
};

//Achieve a stack using two queue
//if q_in not empty,pop elements from q_in and push into q_out until q_in.size=1, then pop the top element of q_in
//if q_in is empty and q_out not empty, pop elements from q_out and push into q_in until q_out.size=1, then pop the top element of q_out
//advantage: when both q_in and q_out is not empty, we only need to pop out the elements of q_in, it save time
template<typename T>
class StackWithTwoQueue {
public:
	void Push(const T &e)
	{
		q_in.push(e);
	}
	void Pop()	
	{
		assert(!q_in.empty() || !q_out.empty());
		if (!q_in.empty()) {
			while (q_in.size() > 1) {
				q_out.push(q_in.front());
				q_in.pop();
			}
			q_in.pop();
		}
		else {
			while (q_out.size() > 1) {
				q_in.push(q_out.front());
				q_out.pop();
			}
			q_out.pop();
		}
	}
	const T& Top()
	{
		assert(!q_in.empty() || !q_out.empty());
		if (!q_in.empty()) {
			while (q_in.size() > 1) {
				q_out.push(q_in.front());
				q_in.pop();
			}
			return q_in.front();
		}
		else {
			while (q_out.size() > 1) {
				q_in.push(q_out.front());
				q_out.pop();
			}
			return q_out.front();
		}
	}
private:
	std::queue<T> q_in;		//to Push
	std::queue<T> q_out;	//to Pop
};

//verify that pop and push of stack is logical or not
template<typename T>
class StackVerifyPopLogic {
public:
	void Input()
	{
		v_in = { 1,2,3,4,5 };
		v_out = { 1,3,5,2,4 };
	}
	void Output()
	{
		cout << "the elements left in stack:" << endl;
		while (!s.empty()) {
			cout << s.top() << " ";
			s.pop();
		}
		cout << endl;
	}
	bool Logical()
	{
		if (v_in.size() != v_out.size() || v_in.empty()) {
			return false;
		}
		int i = 0, j = 0;
		while (i < v_in.size()) {
			if (v_in[i] != v_out[j]) {
				s.push(v_in[i]);
				++i;
			}
			else {
				++i;
				++j;
			}
		}
		//whenj < v_out.size(), s must not empty, so needn't !s.empty() 
		while (j < v_out.size()) {
			if (v_out[j] != s.top()) {
				return false;
			}
			s.pop();
			++j;
		}
		return true;
	}
private:
	std::vector<T> v_in;
	std::vector<T> v_out;
	std::stack<T> s;
};

//achieve two stacks using a array
template<typename T>
class TwoStackWithArray {
public:
	TwoStackWithArray() : capacity(CAPACITY_INIT_SIZE), data(new T[capacity]), first_top(-1), second_top(capacity),  {}
	~TwoStackWithArray() { delete[] data; data(nullptr); }

	void PushFirst(const T &e)
	{
		CheckCapacity();
		data[++first_top] = e;
	}
	void PushSecond()
	{
		CheckCapacity();
		data[--second_top] = e;
	}
	void PopFirst()
	{
		if (-1 == first_top) {
			return;
		}
		--first_top;
	}
	void PopSecond()
	{
		if (capacity == second_top) {
			return;
		}
		++second_top;
	}
	const T& TopFirst()
	{
		assert(-1 < first_top);
		return data[first_top];
	}
	const T& TopSecond()
	{
		assert(capacity > second_top);
		return data[second_top];
	}
	bool EmptyFirst() { return -1 == first_top; }
	bool EmptySecond() { return capacity == second_top; }
	size_t LengthFirst() { return first_top + 1; }
	size_t LengthSecond() { return capacity - second_top; }
private:
	//be careful to singly copy stack1 and stack2 to new data memory
	void CheckCapacity()
	{
		if (first_top + 1 == second_top) {
			T *new_data = new T[2 * capapcity];
			assert(nullptr != new_data);
			memcpy(new_data, data, (first_top + 1) * sizeof(T));	//copy first stack
			memcpy(new_data + capacity + second_top, data + second_top, (capacity - second_top) * sizeof(T));	//copy second stack
			delete[] data;
			data = new_data;
			capacity *= 2;
			second_top += capacity;
		}
	}
public:
	static const size_t CAPACITY_INIT_SIZE = 200;
private:
	T *data;
	int first_top;
	int second_top;
	size_t capacity;
};

#endif // !STACK_QUEUE_INTERVIEW_H
