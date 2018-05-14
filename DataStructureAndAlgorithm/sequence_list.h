#ifndef SEQUENCE_LIST_H
#define SEQUENCE_LIST_H
#endif

template<typename T>
class SequenceList {
public:
	//enum intCode{OK,ERROR};
public:
	SequenceList() : data(new T[LIST_INIT_SIZE]), listsize(LIST_INIT_SIZE), length(0) {}
	~SequenceList() { if(data) delete[] data; }

	////初始化
	//void Init();
	void Destory();
	void Clear();
	void Empty() { return length == 0; }
	size_t Length() { return length; }
	void Print();

	void PushFront(const T& e);
	void PushBack(const T& e);
	void PopFront();
	void PopBack();
	void Insert(size_t pos, const T& e);
	void erase(size_t pos);
	size_t Find(const T& val);
	//删除第一个值为val的元素
	void Remove(const T& val);
	void RemoteAll(const T& val);
public:
	static const size_t LIST_INIT_SIZE = 100;
	static const size_t LIST_INCREMENT_SIZE = 10;
private:
	T* data;
	size_t length;	//当前长度
	size_t listsize; //当前分配空间容量
	//static const int MAX_SIZE = 30;
};