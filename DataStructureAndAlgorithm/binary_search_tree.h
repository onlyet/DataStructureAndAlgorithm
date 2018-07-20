#pragma once

template<typename T>
struct BSTNode {
	T data;
	BSTNode *lchild, rchild, parent;
	BSTNode(const T& data_, BSTNode* lchild_ = nullptr,
		BSTNode* rchild_ = nullptr, BSTNode* parent_ = nullptr) : 
		data(data_), lchild(lchild_), rchild(rchild_), parent(parent_) {}
};

template<typename T>
using BSTPtr = BSTNode<T>*;

template<typename T>
class BSTree {
private:
	BSTPtr root;
public:
	BSTree() : root(nullptr) {}
	~BSTree() { if (root) delete root; }

	BSTPtr Search_Recursive(T data)
	{

	}

	BSTPtr Search_Iterator(T data)
	{

	}

	T Max()
	{

	}

	T Min()
	{

	}

	void Insert(const T& e)
	{
		BSTPtr<T> pre = nullptr, cur = root;
		while (cur) {
			pre = cur;
			if (e < cur->data) {
				cur = cur->lchild;
			}
			else if(e > cur->data){
				cur = cur->rchild;
			}
			else {
				return;
			}
		}
		cur = new BSTNode<T>(e);

		if (!root) {
			root = cur;
		}
		else {
			if (e < pre->data) {
				pre->lchild = cur;
			}
			else {
				pre->rchild = cur;
			}
		}
		cur->parent = pre;
	}

	void Remove(const T& e)
	{

	}

	void Destory()
	{

	}

	void Print()
	{

	}

private:

	BSTPtr<T> Search(BSTPtr<T> root, const T& e)
	{
		BSTPtr<T> cur = root;
		while (cur) {
			if (e < cur->data) {
				cur = cur->lchild;
			}
			else if (e > cur->data) {
				cur = cur->rchild;
			}
			else (e == cur->data) {
				return cur;
			}
		}
	}

	void Remove(BSTPtr root, const T& e)
	{

	}

	void Max(BSTPtr root)
	{

	}

	void Min(BSTPtr root)
	{

	}

	void Destroy(BSTPtr& root)
	{

	}

};