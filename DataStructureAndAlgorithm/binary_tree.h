#pragma once
#ifndef BINARY_TREE_H
#define BINARY_TREE_H
//#include<iostream>


template<typename T>
struct BinaryTreeNode {
	BinaryTreeNode() : lchild(nullptr), rchild(nullptr) {}
	BinaryTreeNode(const T &e) : data(e), lchild(nullptr), rchild(nullptr) {}
	T data;
	BinaryTreeNode *lchild, *rchild;
};
//template<typename T>
//typedef BinaryTreeNode<T> *aa;
//aa<int> a1;
template<typename T>
using BiNode = BinaryTreeNode<T>;
template<typename T>
using BiTree = BinaryTreeNode<T>*;
//tt<int> t1;


template<typename T>
class BinaryTree {
public:
	BinaryTree() : root(nullptr) {}
	~BinaryTree() { Destory(Root()); }
	BiTree<T> Root() { return root; }
	bool Empty() { return nullptr == root; }
	T Value(BiTree<T> head) { return head->data; }
	void Assign(BiTree<T> head, value) { head->data = value; }
	void Create(BiTree<T> head);
	void Destory(BiTree<T> head);
	size_t Depth(BiTree<T> head);
	//BiTree<T> Parent(BiTree<T> head);
	//BiTree<T> LeftChild(BiTree<T> head);
	//BiTree<T> RightSibling(BiTree<T> head);
	void InsertChild(BiTree<T> head, const T &e);
	void DeleteChild(BiTree<T> head);

	void PreorderTraversal(BiTree<T> head);
	void InorderTraversal(BiTree<T> head);
	void PostorderTraversal(BiTree<T> head);

private:
	BiTree<T> root;
};

template<typename T>
void BinaryTree<T>::Create(BiTree<T> head)
{
	char c;
	/*if ((c = cin.get()) == '#') {
		return;
	}*/
	cin >> c;
	if ('#' == c) {
		head = nullptr;
		return;
	}
	//if (nullptr == head) {
	//	head = new BiNode<T>:
	//}
	head = new BiNode<T>;
	//if (nullptr == head) {
	//	throw std::bad_alloc("new() error");
	//}
	cin >> head->data;
	Create(head->lchild);
	Create(head->rchild);
}

template<typename T>
void BinaryTree<T>::Destory(BiTree<T> head)
{
	if (nullptr != head) {
		Destory(head->lchild);
		Destory(head->rchild);
		delete head;
		head = nullptr;
	}
}

template<typename T>
size_t BinaryTree<T>::Depth(BiTree<T> head)
{
	if (nullptr == head) {
		return 0;
	}
	size_t ld = Depth(head->lchild);
	size_t rd = Depth(head->rchild);
	if (ld > rd) {
		return ld + 1;
	}
	else {
		retrun rd + 1;
	}
}

template<typename T>
void BinaryTree<T>::InsertChild(BiTree<T> head, const T & e)
{
	if (nullptr == head) {
		head = new BiNode<T>(e);
	}
	else if (e < head->data) {
		InsertChild(head->lchild, e);
	}
	else {
		InsertChild(head->rchild, e);
	}
}

template<typename T>
void BinaryTree<T>::DeleteChild(BiTree<T> head)
{
	if (nullptr == head) {
		return;
	}
	DeleteChild(head->lchild);
	DeleteChild(head->rchild);
	delete head;
	head = nullptr;
}

template<typename T>
void BinaryTree<T>::PreorderTraversal(BiTree<T> head)
{
	if (head) {
		cout << head->data << " ";
		PreorderTraversal(head->lchild);
		PreorderTraversal(head->rchild);
	}
}

template<typename T>
void BinaryTree<T>::InorderTraversal(BiTree<T> head)
{
	if (head) {
		InorderTraversal(head->lchild);
		cout << head->data << " ";
		InorderTraversal(head->rchild);
	}
}

template<typename T>
void BinaryTree<T>::PostorderTraversal(BiTree<T> head)
{
	if (head) {
		PostorderTraversal(head->lchild);
		PostorderTraversal(head->rchild);
		cout << head->data << " ";
	}
}

#endif // !BINARY_TREE_H

