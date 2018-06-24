//#include"DoubleLinkedList.h"
//#include<iostream>
//#include<vector>
//
//using namespace std;
//
//template<typename T>
//DoubleLinkedList<T>::DoubleLinkedList()
//{
//	phead = new DLLNode;
//	phead->prev = NULL;
//	phead->next = NULL;
//	phead->data = 0;
//	m_count = 0;
//}
//
//template<typename T>
//DoubleLinkedList<T>::DoubleLinkedList(T data)
//{
//	phead = new DLLNode;
//	phead->next = phead->prev = phead;
//	phead->data = data;
//	m_count = 0;
//}
//
//template<typename T>
//DoubleLinkedList<T>::~DoubleLinkedList()
//{
//	delete phead;
//	phead = NULL;
//}
//
//template<typename T>
//int DoubleLinkedList<T>::insert_first(T data)
//{
//	DLLNode *phead = new DLLNode(phead, phead->next, data);
//
//	phead->next->head = phead;	//prev of first node point to new node
//	phead->next = phead;		//next of head node point to new node 
//	phead->data = data;
//	++m_count;
//
//	return 0;
//}
//
//template<typename T>
//int DoubleLinkedList<T>::insert_last(T data)
//{
//	DLLNode *phead = new DLLNode(phead->prev, phead, data);
//
//	phead->prev->next = phead;
//	phead->prev = phead;
//	phead->data = data;
//	++m_count;
//
//	return 0;
//}