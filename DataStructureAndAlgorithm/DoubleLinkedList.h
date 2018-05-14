//#pragma once
//
///* Double circle linked list */
//template<typename T>
//struct DoubleLinkedListNode
//{
//	DoubleLinkedListNode *prev;
//	DoubleLinkedListNode *next;
//	T data;
//
//	// convenient to new a node
//	DoubleLinkedListNode(DoubleLinkedListNode *prev,
//		DoubleLinkedListNode *next,
//		T data)
//	{
//		this->prev = prev;
//		this->next = next;
//		this->data = data;
//	}
//
//};
//
//template<typename T>
//class DoubleLinkedList
//{
//public:
//	DoubleLinkedList();
//	DoubleLinkedList(T data);
//	~DoubleLinkedList();
//
//public:
//	int insert_first(T data);
//	int insert_last(T data);
//	Delete();
//	GetElem();
//	SetElem();
//
//private:
//	typedef DoubleLinkedListNode<T> DLLNode;
//	
//		DLLNode *phead;	// head pointer
//	//DoubleLinkedListNode<T> *pNode;
//	int m_count;
//};