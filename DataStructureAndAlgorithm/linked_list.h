#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#endif // !LINKED_LIST_H

struct LinkedListNode {
	
	LinkedListNode *next;
};

template<typename T>
class ListBase{
public:
	ListBase() {}
	~ListBase() {}
public:
	virtual bool Insert(size_t pos, const T& e);
	virtual bool Erase(size_t pos);
	virtual bool Set(size_t pos, const T& e);
	virtual bool Get(size_t pos, T& e);
	virtual bool Empty();
	virtual int Find(const T& e);
	virtual size_t Length();
};

template<typename T>
class LinkedList : public ListBase<T>{
public:
private:
	struct LinkedListNode {
		T data;
		LinkedListNode *next;
	};
	LinkedListNode node;
	size_t length;
};
