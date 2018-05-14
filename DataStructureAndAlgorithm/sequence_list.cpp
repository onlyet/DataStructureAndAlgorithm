#include"sequence_list.h"
#include<iostream>

using namespace std;

//const size_t  LIST_INIT_SIZE = 100;
//const size_t LIST_INCREMENT_SIZE = 10;

//template<typename T>
//void SequenceList<T>::Init()
//{
//	data = new T[LIST_INIT_SIZE];
//	listsize = LIST_INIT_SIZE;
//}

template<typename T>
void SequenceList<T>::Clear()
{
	delete[] data;
	data = new T[LIST_INIT_SIZE];
	listsize = LIST_INIT_SIZE;
	length = 0;
}

template<typename T>
void SequenceList<T>::Destory()
{
	delete[] data;
	length = listsize = 0;
}

template<typename T>
void SequenceList<T>::Print()
{
	for (int i = 0; i < length; ++i) {
		cout << data[i] << " ";
	}
	cout << endl;
}

template<typename T>
void SequenceList<T>::PushFront(const T& e)
{

}

template<typename T>
void SequenceList<T>::PushBack(const T& e)
{
	Insert(length + 1; e);
}

template<typename T>
void SequenceList<T>::PopFront()
{
}

template<typename T>
void SequenceList<T>::PopBack()
{
}

//pos从1开始，data下标从0开始
template<typename T>
void SequenceList<T>::Insert(size_t pos, const T& e)
{
	if (1 > pos || pos > length + 1) {
		cout << "pos out of range" << endl;
		return;
	}
	if (LIST_INIT_SIZE == length) {
		T* tmp = new T[listsize + LIST_INCREMENT_SIZE];
		delete[] = data;
		data = tmp;
		listsize += LIST_INCREMENT_SIZE;
	}
	for (int cur = length; cur >= pos; --cur) {
		data[cur - 1] = data[cur];
	}
	data[pos - 1] = e;
	++length;
}

template<typename T>
void SequenceList<T>::erase(size_t pos)
{
	size_t i = pos - 1;	//同一使用下标方便理解
	if (0 > i || i > length - 1) {
		cout << "pos out of range" << endl;
		return;
	}
	for (int cur = i; cur < length - 1; ++cur) {
		data[cur] = data[cur + 1];
	}
	--length;
}

template<typename T>
size_t SequenceList<T>::Find(const T& val)
{
	return size_t();
}

template<typename T>
void SequenceList<T>::Remove(const T& val)
{
}

template<typename T>
void SequenceList<T>::RemoteAll(const T& val)
{
}

