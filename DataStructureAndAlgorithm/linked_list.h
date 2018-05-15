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
	virtual void Insert(size_t pos, const T& e);
	virtual void Erase(size_t pos);
	virtual void Set(size_t pos, const T& e);
	virtual void Get(size_t pos, T& e);
	virtual int Find(const T& e);
	virtual void find();
	virtual size_t Length();
};

class LinkedList {
public:
private:
	LinkedList* next;
};
