#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#endif // !LINKED_LIST_H
#include<string>

template<typename T>
class ListBase{
public:
	//ListBase() {}
	virtual ~ListBase() {}
public:
	virtual bool Insert(size_t pos, const T& e) = 0;
	virtual bool Erase(size_t pos, T& e) = 0;
	virtual void Print() = 0;
	virtual bool Set(size_t pos, const T& e) = 0;
	virtual bool Get(size_t pos, T& e) = 0;
	virtual bool Empty() = 0;
	virtual int Find(const T& e) = 0;
	virtual size_t Length() = 0;
	virtual void Clear() = 0;
};

template<typename T>
struct LinkedListNode {
	LinkedListNode() : pnext(nullptr) {}
	T data;
	LinkedListNode *pnext;
};

//带头结点的单链表
template<typename T>
class LinkedList : public ListBase<T>{
public:
	LinkedList() : phead(new LinkedListNode<T>) {}
	~LinkedList() { Clear(); if(phead) delete phead; }
public:

	bool Insert(size_t pos, const T& e) override;
	//删除和插入不同，插入只有保证第pos-1个结点存在就行，而删除要保证第pos-1和pos个结点都存在
	bool Erase(size_t pos, T& e) override;
	void Print() override;
	size_t Length() override;
	bool Set(size_t pos, const T& e) override;
	bool Get(size_t pos, T& e) override;
	bool Empty() override { return 0 == Length(); }
	//顺序查找，返回data=e的第一个结点位置，如果找不到返回-1
	int Find(const T& e) override;
	void Clear() override;

	bool PushBack(const T& e) { return Insert(Length() + 1, e); }
	bool PushFront(const T& e) { return Insert(1, e); }
	bool PopBack(T& e) { return Erase(Length(), e); }
	bool PopFront(T& e) { return Erase(1, e); }

	//void FrontCreate(T n) {}

	template<typename T2>
	void FrontCreate(T2 n) {}
	template<>	//类模版的成员函数模版的特化
	void FrontCreate(int n) {
		for (int i = 0; i < n; ++i) {
			LinkedListNode<T> *s = new LinkedListNode<T>;
			s->pnext = phead->pnext;
			phead->pnext = s;
			s->data = i;
		}
	}
	template<typename T2>
	void BackCreate(T2 n) {}
	template<>
	void BackCreate(int n) {
		LinkedListNode<T> *tail = phead;
		for (int i = 0; i < n; ++i) {
			LinkedListNode<T> *s = new LinkedListNode<T>;
			s->data = i;
			tail->pnext = s;
			tail = s;
		}
	}

	LinkedListNode<T>* Head();
	//非递归反转链表,返回反转后链表的头结点
	LinkedListNode<T>* reverse();
	LinkedListNode<T>* recursive_reverse(LinkedListNode<T>* cur);

	//返回第pos个结点的指针，pos=0代表头结点
	virtual LinkedListNode<T>* Locate(size_t pos);

	//冒泡排序法，升序
	void BubbleSort();
	//返回倒数第k个结点，（一般不知道链表长度），采用相对位移
	//第一个结点和第k个结点同时后移，当第k个结点走到最后一个结点时，第一个结点走到倒数第k个结点
	LinkedListNode<T>* FindKLast(int k);
	//删除倒数第k个结点
	bool EraseKLast(int k, T &e);
	//倒序打印（使用递归）
	void ReversePrint(LinkedListNode<T>* cur);
	//不允许遍历，在pos位置之前插入结点
	void InsertBefore(LinkedListNode<T>* pos, const T &e);
	//不允许遍历，删除第n个结点
	void EraseN(LinkedListNode<T> *pos, const T &e);
	//约瑟夫环
	LinkedListNode<T>* JosephCircle(size_t food);
	//找到中间结点
	LinkedListNode<T>* FindMiddle();
	//判断是否有环，有环则返回快慢指针的相遇点
	LinkedListNode<T>* GetCircleMeetNode();
	//如果链表有环，求环的长度，传入参数：相遇点
	size_t CircleLen(LinkedListNode<T> *meet_point);
	//如果链表有环，求环的入口点，传入参数：相遇点
	LinkedListNode<T>* GetCircleEntryNode(LinkedListNode<T> *meet_point);
	
private:
	LinkedListNode<T>* phead;
	//size_t length;	//不用length也不影响
};

template<typename T>
LinkedListNode<T>* LinkedList<T>::Locate(size_t pos)
{
	if (pos < 0) {
		return nullptr;
	}
	int i = 0;	//第i个结点
	LinkedListNode<T>* p = phead;
	while (p && i < pos) {	//pos=0的时候返回头结点,p指向第n个结点时i=n+1
		p = p->pnext;
		++i;
	}
	return p;
}

template<typename T>
bool LinkedList<T>::Insert(size_t pos, const T& e)
{
	LinkedListNode<T>* p = Locate(pos - 1);
	if (!p) {
		cout << "Insert() error" << endl;
		return false;
	}

	LinkedListNode<T> *s = new LinkedListNode<T>;
	if (!s) {
		return false;	//应不应该抛出异常？
	}
	s->data = e;
	s->pnext = p->pnext;
	p->pnext = s;
	//++length;
	return true;
}

//不能删除头结点
template<typename T>
bool LinkedList<T>::Erase(size_t pos, T& e)
{
	LinkedListNode<T>* p = Locate(pos - 1);
	if (!p || !p->pnext) {	//验证第pos-1和第pos个结点存在
		cout << "Erase() error" << endl;
		return false;
	}
	LinkedListNode<T>* s = p->pnext;
	e = s->data;
	p->pnext = s->pnext;
	delete s;
	//--length;
	return true;
}

template<typename T>
void LinkedList<T>::Print()
{
	LinkedListNode<T> *p = phead->pnext;	//第一个结点
	while (p) {
		cout << p->data << " ";
		p = p->pnext;
	}
	cout << endl;
}

template<typename T>
size_t LinkedList<T>::Length()
{
	LinkedListNode<T>* p = phead->pnext;
	int cnt = 0;
	while (p) {
		p = p->pnext;
		++cnt;
	}
	return cnt;
}

template<typename T>
bool LinkedList<T>::Set(size_t pos, const T& e)
{
	LinkedListNode<T>* p = Locate(pos);
	if (!p) {
		cout << "Set() error" << endl;
		return false;
	}
	p->data = e;
	return true;
}

template<typename T>
bool LinkedList<T>::Get(size_t pos, T& e)
{
	LinkedListNode<T>* p = Locate(pos);
	if (!p) {
		cout << "Get() error" << endl;
		return false;
	}
	e = p->data;
	return true;
}

template<typename T>
int LinkedList<T>::Find(const T& e)
{
	int i = 1;
	LinkedListNode<T>* p = phead->pnext;
	while (p) {
		if (e == p->data) {
			return i;
		}
		p = p->pnext;
		++i;
	}
	return -1;
}

template<typename T>
void LinkedList<T>::Clear()
{
	size_t len = Length();
	T e;
	for (size_t i = 0; i < len; ++i) {
		PopBack(e);
	}
}

template<typename T>
LinkedListNode<T>* LinkedList<T>::Head()
{
	return phead;
}

//单链表的反转需要三个结点指针：分别指向上一个，当前，下一个结点
//首先让第一个结点的指针域为NULL
//然后在循环里next=cur->next,cur->next->pre,这样就完成一次反转，接着++pre，++cur,
//循环退出的条件是cur=NULL
//最后将head->next=pre
//反转不包括头结点
template<typename T>
LinkedListNode<T>* LinkedList<T>::reverse()
{
	if (Length() < 2) {
		cout << "Length of LinkedList less than 2" << endl;
		return;
	}
	LinkedListNode<T> *pre = phead->pnext, *cur = pre->pnext, *next;	

	phead->pnext->pnext = nullptr;
	while (cur) {
		next = cur->pnext;
		cur->pnext = pre;
		pre = cur;
		cur = next;
	}
	phead->pnext = pre;
	return phead;
}

template<typename T>
LinkedListNode<T>* LinkedList<T>::recursive_reverse(LinkedListNode<T>* cur)
{
	//cur->pnext=NULL是递归退出条件，并且保证链表结点>=2
	if (!cur || !cur->pnext) {
		return cur;
	}
	LinkedListNode<T> *last = recursive_reverse(cur->pnext);	//递归到最后一个结点
	if (!last->pnext) {
		phead->pnext = last; //让头结点指向反转后第一个结点（即反转前最后一个结点）
	}
	cur->pnext->pnext = cur;	//让下一个结点指向当前结点
	cur->pnext = nullptr;
	return phead; 
}

template<typename T>
void LinkedList<T>::BubbleSort()
{
	int flag = Length() - 1;	//排序结束标志
	while (flag) {
		int unordered = flag;	//unordered表示无序区的末尾，即该下标之后的元素都是有序的
		flag = 0;
		LinkedListNode<T> *l = phead->pnext, *r = l->pnext;
		for (int i = 0; i < unordered; ++i) {
			if (r->data < l->data) {
				swap(r->data, l->data);
				flag = i;
			}
			l = l->pnext;
			r = r->pnext;
		}
	}
}

template<typename T>
LinkedListNode<T>* LinkedList<T>::FindKLast(int k)
{
	//int n = Length() - k + 1;
	LinkedListNode<T> *cur = Locate(k);	//第k个结点
	LinkedListNode<T> *klast = phead->pnext;	//第一个结点
	while (cur->pnext) {
		cur = cur->pnext;
		klast = klast->pnext;
	}
	cout << "find the element in : "<< k << " last, data: " << klast->data << endl;
	return klast;
}

template<typename T>
bool LinkedList<T>::EraseKLast(int k, T& e)
{
	LinkedListNode<T> *p = FindKLast(k + 1);	//定位到倒数第k+1个结点
	if (!p || !p->pnext) {
		cout << "Erase() error" << endl;
		return false;
	}
	LinkedListNode<T> *s = p->pnext;
	e = p->pnext->data;
	p->pnext = s->pnext;
	delete s;
}

template<typename T>
void LinkedList<T>::ReversePrint(LinkedListNode<T>* cur)
{
	if (!cur || !cur->pnext) {
		return;
	}
	ReversePrint(cur->pnext);
	cout << cur->pnext->data << " ";
	if (cur == phead) {
		cout << endl;
	}
}

template<typename T>
void LinkedList<T>::InsertBefore(LinkedListNode<T>* pos, const T& e)
{
	//在pos之后插入结点，然后交换pos和s的data
	LinkedListNode<T> *s = new LinkedListNode<T>;
	s->pnext = pos->pnext;
	pos->pnext = s;
	s->data = pos->data;
	pos->data = e;
}

template<typename T>
void LinkedList<T>::EraseN(LinkedListNode<T>* pos, const T& e)
{
	e = pos->data;
	pos->data = pos->pnext->data;
	LinkedListNode<T> *s = pos->pnext;
	pos->pnext = s->pnext;
	delete s;
}

//合并两个升序的单链表，合并后依然升序
template<typename T>
LinkedListNode<T>* Merge(LinkedListNode<T>* lhs, LinkedListNode<T>* rhs)
{
	LinkedListNode<T> *p = lhs->pnext, *q = rhs->pnext;
	LinkedList<T> *l = new LinkedList<T>;
	LinkedListNode<T> *last = l->Head();

	while (p && q) {
		LinkedListNode<T> *s = new LinkedListNode<T>;
		if (p->data < q->data) {
			s->data = p->data;
			p = p->pnext;
		}
		else {
			s->data = q->data;
			q = q->pnext;
		}
		last->pnext = s;
		last = s;
	}
	while (p) {
		LinkedListNode<T> *s = new LinkedListNode<T>;
		s->data = p->data;
		p = p->pnext;
		last->pnext = s;
		last = s;
	}
	while (q) {
		LinkedListNode<T> *s = new LinkedListNode<T>;
		s->data = q->data;
		q = q->pnext;
		last->pnext = s;
		last = s;
	}

	return l->Head();
}

//打印某链表的元素
template<typename T>
void Print(LinkedListNode<T>* p)
{
	if (!p || !p->pnext) {
		return;
	}
	while (p->pnext) {
		cout << p->pnext->data << " ";
		p = p->pnext;
	}
	cout << endl;
}

//如果有环不就无限循环了？ 
template<typename T>
LinkedListNode<T>* LinkedList<T>::FindMiddle()
{
	if (!phead || !phead->pnext) {
		return nullptr;
	}
	LinkedListNode<T> *fast = phead, *slow = phead;
	while (fast && fast->pnext) {
		slow = slow->pnext;
		fast = fast->pnext->pnext;
	}
	return slow;
}

template<typename T>
LinkedListNode<T>* LinkedList<T>::GetCircleMeetNode()
{
	LinkedListNode<T> *fast = phead->pnext, *slow = phead->pnext;
	while (fast && fast->pnext) {	//快指针必须保证fast->pnext!=null, 否则fast->pnext->pnext会导致解引用空指针
		fast = fast->pnext->pnext;
		slow = slow->pnext;
		if (fast == slow) {
		    return fast;
		}
	}
	return nullptr;
}

template<typename T>
size_t LinkedList<T>::CircleLen(LinkedListNode<T> *meet_point)
{
	if (!meet_point) {
		return 0;
	}
	size_t cnt = 1;
	LinkedListNode<T> *cur = meet_point->pnext;
	while (cur != meet_point) {
		++cnt;
		cur = cur->pnext;
	}
	return cnt;
}

template<typename T>
LinkedListNode<T>* LinkedList<T>::GetCircleEntryNode(LinkedListNode<T> *meet_point)
{
	if (!meet_point) {
		return nullptr;
	}
	LinkedListNode<T> *p = phead->pnext;	//从第一个结点开始
	LinkedListNode<T> *q = meet_point;		//从相遇点开始
	while (p) {
		p = p->pnext;
		q = q->pnext;
		if (p == q) {
			return p;	//当p，q相遇的时候，该点就是入口点
		}
	}
}

//判断两无环单链表是否有交点
//如果有链表是有环的，那将陷入死循环
template<typename T>
bool HasCrossNode(LinkedListNode<T> *l, LinkedListNode<T> *r)
{
	if (!l || !r || !l->pnext || !r->pnext) {
		return false;
	}
	LinkedListNode<T> *p = l->pnext, *q = r->pnext;
	while (p->pnext) {
		p = p->pnext;
	}
	while (q->pnext) {
		q = q->pnext;
	}
	if (p == q) {
		return true;
	}
	else {
		return false;
	}
}

//返回两无环单链表的交点
//转化成求有环单链表的入口点，这种方法时间复杂度好像太高了？
template<typename T>
LinkedListNode<T> *GetCrossNode(LinkedList<T> *l, LinkedList<T> *r)
{
	//如果存在链表是有环的，则不能用该函数确定交点
	if (l->GetCircleMeetNode() || r->GetCircleMeetNode()) {
		return nullptr;
	}
	//判断是否有交点（适用于两无环单链表）
	if (!HasCrossNode(l->Head(), r->Head())) {
		return nullptr;
	}
	LinkedListNode<T> *p = l->pnext;
	while (p->pnext) {
		p = p->pnext;	//遍历到最后一个结点
	}
	p->pnext = l->pnext;	//让链表l尾首相连，成环

	//获得新环的相遇点
	LinkedListNode<T> *meet_node = r->GetCircleMeetNode();
    p->pnext = nullptr;	//断开链表l的环
	if (!meet_node) {
		return nullptr;
	}

	return r->GetCircleEntryNode(meet_node);		//获得新环的入口点，即两无环单链表的交点
}

//判断两有环单链表是否有交点
//两个有环单链表有交点，则它们共环，则问题转化为：判断表l环上任意一点是否在表r环上
template<typename T>
bool CircleHasCrossNode(LinkedList<T> *l, LinkedList<T> *r)
{
	LinkedListNode<T> *l_meet_node = l->GetCircleMeetNode();
	LinkedListNode<T> *r_meet_node = r->GetCircleMeetNode();
	if (!l_meet_node || !r_meet_node) {
		return false;
	}
	if (l_meet_node == r_meet_node) {
		return true;
	}
	LinkedListNode<T> *p = l_meet_node->pnext;
	while (p != l_meet_node) {
		if (p == r_meet_node) {
			return true;
		}
		p = p->pnext;
	}
	return false;
}

//返回两有环单链表的交点
template<typename T>
bool CircleGetFirstCrossNode(LinkedList<T> *l, LinkedList<T> *r, LinkedListNode<T> *pn)
{
	LinkedListNode<T> *l_meet_node = l->GetCircleMeetNode();
	LinkedListNode<T> *r_meet_node = r->GetCircleMeetNode();
	if (!l_meet_node || !r_meet_node) {
		return false;
	}
	if (!CircleHasCrossNode(l, r)) {
		return false;
	}
	LinkedListNode<T> *p = l->Head()->pnext;
	LinkedListNode<T> *q = r->Head()->pnext;
	size_t l_len = 1, r_len = 1;
	while (p != l_meet_node) {
		p = p->pnext;
		++l_len;
	}
	while (q != r_meet_node) {
		q = q->pnext;
		++r_len;
	}
	p = l->Head()->pnext;
	q = r->Head()->pnext;
	if (l_len < r_len) {
		for (size_t i = 0; i < r_len - l_len; ++i) {
			p = p->pnext;
		}
	}
	else {
		for (size_t i = 0; i < l_len - r_len; ++i) {
			q = q->pnext;
		}
	}
	while (p != q) {
		p = p->pnext;
		q = q->pnext;
	}
	pn = p;
	return true;
}