#pragma once
#ifndef STACK_QUEUE_INTERVIEW_H
#define STACK_QUEUE_INTERVIEW_H
#include<stack>
#include<queue>

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


#endif // !STACK_QUEUE_INTERVIEW_H
