#ifndef SEQUENCE_LIST_H
#define SEQUENCE_LIST_H
#endif

template<typename T>
class SequenceList {
public:
	//enum intCode{OK,ERROR};
public:
	SequenceList() : data(new T[LIST_INIT_SIZE * sizeof(T)]), stack_size(LIST_INIT_SIZE), length(0) {}
	~SequenceList() { if (data) { delete[] data; data = nullptr; } }

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
	void Erase(size_t pos);
	//返回第一个匹配val的元素位置
	int Find(const T& val);
	//删除第一个值为val的元素
	void Remove(const T& val);
	void RemoteAll(const T& val);
public:
	static const size_t LIST_INIT_SIZE = 3;
	static const size_t LIST_INCREMENT_SIZE = 1;
private:
	T* data;
	size_t length;	//当前长度
	size_t stack_size; //当前分配空间容量
	//static const int MAX_SIZE = 30;
};

//template<typename T>
//void SequenceList<T>::Init()
//{
//	data = new T[LIST_INIT_SIZE];
//	stack_size = LIST_INIT_SIZE;
//}

template<typename T>
void SequenceList<T>::Clear()
{
	cout << "Clear()" << endl;
	delete[] data;
	data = new T[LIST_INIT_SIZE];
	stack_size = LIST_INIT_SIZE;
	length = 0;
}

template<typename T>
void SequenceList<T>::Destory()
{
	cout << "Destory()" << endl;
	delete[] data;
	data = nullptr;	//delete一定要设nullptr，否则会不小心释放两次引起的未定义行为
	length = stack_size = 0;
}


template<typename T>
void SequenceList<T>::Print()
{
	cout << "Print()" << endl;
	for (int i = 0; i < length; ++i) {
		cout << data[i] << " ";
	}
	cout << endl;
}


template<typename T>
void SequenceList<T>::PushFront(const T& e)
{
	Insert(1, e);
}

template<typename T>
void SequenceList<T>::PushBack(const T& e)
{
	Insert(length + 1, e);
}

template<typename T>
void SequenceList<T>::PopFront()
{
	Erase(1);
}

template<typename T>
void SequenceList<T>::PopBack()
{
	Erase(length);
}

//pos从1开始，data下标从0开始
template<typename T>
void SequenceList<T>::Insert(size_t pos, const T& e)
{
	if (1 > pos || pos > length + 1) {
		cout << "pos out of range" << endl;
		return;
	}
	if (stack_size == length) {
		T* tmp = new T[stack_size + LIST_INCREMENT_SIZE];
		memcpy(tmp, data, length * sizeof(T));
		delete[] data;
		data = tmp;
		stack_size += LIST_INCREMENT_SIZE;
	}
	for (int cur = length; cur >= pos; --cur) {
		data[cur] = data[cur - 1];
	}
	data[pos - 1] = e;
	++length;
}

template<typename T>
void SequenceList<T>::Erase(size_t pos)
{
	size_t i = pos - 1;	//统一使用下标方便理解
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
int SequenceList<T>::Find(const T& val)
{
	for (int i = 0; i < length; ++i) {
		if (val == data[i]) {
			cout << "find " << val << " at position: " << i + 1 << endl;
			return i + 1;
		}
	}
	return -1;
}

template<typename T>
void SequenceList<T>::Remove(const T& val)
{
	for (int i = 0; i < length; ++i) {
		if (val == data[i]) {
			Erase(i + 1);
			return;
		}
	}
}

template<typename T>
void SequenceList<T>::RemoteAll(const T& val)
{
	for (int i = 0; i < length;) {
		//删除了元素i不++，因为data[i]被重新赋值了
		if (val == data[i]) {
			Erase(i + 1);
		}
		else {
			++i;
		}
	}
}



