#pragma once
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

template<typename T>
struct BinaryTreeNode {
	BinaryTreeNode() : lchild(nullptr), rchild(nullptr) {}
	T data;
	BinaryTreeNode *lchild, *rchild;
};
template<typename T>
typedef BinaryTreeNode<T> *aa;
aa<int> a1;
template<typename T>
using tt = BinaryTreeNode<T>*;
tt<int> t1;


template<typename T>
class BinaryTree {
public:
	BinaryTree();
	~BinaryTree();
	void Init();
	void Destory();
	void Create();
	void Clear();
	bool Empty();
	size_t Depth();
	BinaryTreeNode<T>* Root(T);
	T Value(BinaryTreeNode<T>* cur_e);
	void Assign(BinaryTreeNode<T>* cur_e, value);
	BinaryTreeNode<T>* Parent(BinaryTreeNode<T> *cur_e);
	BinaryTreeNode<T>* LeftChild(BinaryTreeNode<T> *cur_e);
	BinaryTreeNode<T>* RightSibling(BinaryTreeNode<T> *cur_e);
	InsertChild(BinaryTreeNode<T> *p, i, BinaryTree*);
	DeleteChild(BinaryTreeNode<T> *p, i);

	void PreorderTraversal(BinaryTreeNode<T> *head);
	void InorderTraversal(BinaryTreeNode<T> *head);
	void PostorderTraversal(BinaryTreeNode<T> *head);

private:
	BinaryTreeNode<T> head;
};

template<typename T>
void BinaryTree<T>::Create()
{
}

template<typename T>
void BinaryTree<T>::PreorderTraversal(BinaryTreeNode<T> *head)
{
	if (head) {
		cout << head->data << " ";
		PreorderTraversal(head->lchild);
		PreorderTraversal(head->rchild);
	}
}

template<typename T>
void BinaryTree<T>::InorderTraversal(BinaryTreeNode<T>* head)
{
	if (head) {
		InorderTraversal(head->lchild);
		cout << head->data << " ";
		InorderTraversal(head->rchild);
	}
}

template<typename T>
void BinaryTree<T>::PostorderTraversal(BinaryTreeNode<T>* head)
{
	if (head) {
		PostorderTraversal(head->lchild);
		PostorderTraversal(head->rchild);
		cout << head->data << " ";
	}
}

#endif // !BINARY_TREE_H

