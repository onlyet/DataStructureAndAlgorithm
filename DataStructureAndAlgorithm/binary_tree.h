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
	void Destroy() { Destroy(&m_root); }
	BinaryTree() : m_root(nullptr) {}
	BinaryTree(const T *a, size_t sz, const T &invalid)
	{
		size_t index = 0;
		m_root = Create(a, sz, invalid, index);
	}
	BinaryTree(const BinaryTree &rhs)
	{
		m_root = Copy(rhs->m_root);
	}
	BinaryTree& operator=(const BinaryTree &rhs)
	{
		if (this != &rhs) {
			Destroy(&m_root);
			m_root = Copy(rhs->m_root);
		}
		return *this;
	}
	~BinaryTree() { Destroy(&m_root); }

	BiTree<T> Root() { return m_root; }
	bool Empty() { return nullptr == m_root; }
	T Value(BiTree<T> root) { return root->data; }
	void Assign(BiTree<T> root, const T &value) { root->data = value; }
	void Create(BiTree<T> root)
	{
		char c;
		/*if ((c = cin.get()) == '#') {
		return;
		}*/
		cin >> c;
		if ('#' == c) {
			root = nullptr;
			return;
		}
		root = new BiNode<T>;
		//if (nullptr == root) {
		//	throw std::bad_alloc("new() error");
		//}
		cin >> root->data;
		Create(root->lchild);
		Create(root->rchild);
	}

	size_t Depth()
	{
		return Depth_(m_root);
	}
	//结点数
	size_t Size()
	{
		return Size_(m_root);
	}

	size_t LeafSize()
	{
		return LeafSize_(m_root);
	}

	void PreorderTraversal()
	{
		PreorderTraversal_(m_root);
	}

	void InorderTraversal()
	{
		InorderTraversal_(m_root);
	}

	void PostoederTraversal()
	{
		PostorderTraversal_(m_root);
	}

	void LevelTraversal()
	{
		LevelTraversal_(m_root);
	}

	//时间复杂度：O(n),空间复杂度：O(n)
	void NonRecursivePreorder()
	{
		std::stack<BiTree<T>> s;
		BiTree<T> top;
		if (nullptr != m_root) {
			s.push(m_root);
			while (!s.empty()) {
				top = s.top();
				cout << top->data << "->";
				s.pop();
				if (nullptr != top->rchild) {
					s.push(top->rchild);
				}
				if (nullptr != top->lchild) {
					s.push(top->lchild);
				}
			}
		}
	}

	//时间复杂度：O(n),空间复杂度：O(n)
	void NonRecursivePreorder_v2()
	{
		std::stack<BiTree<T>> s;
		BiTree<T> cur = m_root;
		while (nullptr != cur || !s.empty()) {
			while (nullptr != cur) {
				cout << cur->data << "->";
				s.push(cur);
				cur = cur->lchild;
			}
			//if (!s.empty()) {
				cur = s.top();
				s.pop();
				cur = cur->rchild;
			//}
		}
	}

	//时间复杂度的：O(n),空间复杂度：O(n)
	void NonRecursiveInorder()
	{
		std::stack<BiTree<T>> s;
		BiTree<T> cur = m_root;
		while (nullptr != cur || !s.empty()) {
			while (nullptr != cur) {
				s.push(cur);
				cur = cur->lchild;
			}
			//if (!s.empty()) {
				cur = s.top();	//在打印当前结点后，还要访问该结点的右子树
				cout << cur->data << "->";
				s.pop();
				cur = cur->rchild;
			//}
		}

	}

	//时间复杂度的：O(n),空间复杂度：O(n)
	void NonRecursivePostorder()
	{
		std::stack<BiTree<T>> s;
		BiTree<T> cur;
		BiTree<T> pre = nullptr;
		if (nullptr == m_root) {
			return;
		}
		s.push(m_root);
		while (!s.empty()) {
			cur = s.top();
			//如果该结点的左右孩子结点都为nullptr，或者该结点的孩子结点已经访问过，则访问该结点
			if ((nullptr == cur->lchild && nullptr == cur->rchild) ||
				(nullptr != pre && (pre == cur->lchild || pre == cur->rchild))) {
				cout << cur->data << "->";
				s.pop();
				pre = cur;
			}
			//否则，先将右结点压栈，再将左结点压栈
			else {
				if (nullptr != cur->rchild) {
					s.push(cur->rchild);
				}
				if (nullptr != cur->lchild) {
					s.push(cur->lchild);
				}
			}
		}
	}

	//时间复杂度的：O(n),空间复杂度：O(1)
	void NonRecursivePreorder_O1()
	{
		BiTree<T> pre, cur = m_root;
		while (nullptr != cur) {
			if (nullptr == cur->lchild) {
				cout << cur->data << "->";
				cur = cur->rchild;
			}
			else {
				pre = cur->lchild;
				while (nullptr != pre->rchild && pre->rchild != cur) {
					pre = pre->rchild;
				}
				if (nullptr == pre->rchild) {
					cout << cur->data << "->";
					pre->rchild = cur;
					cur = cur->lchild;
				}
				else {
					pre->rchild = nullptr;
					cur = cur->rchild;
				}
			}
		}
	}

	//时间复杂度的：O(n),空间复杂度：O(1)
	void NonRecursiveInorder_O1()
	{
		BiTree<T> pre, cur = m_root;
		while (nullptr != cur) {
			if (nullptr == cur->lchild) {
				cout << cur->data << "->";
				cur = cur->rchild;
			}
			else {
				pre = cur->lchild;
				//找到cur的前驱结点
				while (nullptr != pre->rchild && pre->rchild != cur) {
					pre = pre->rchild;
				}
				//将pre的右孩子指向cur
				if (nullptr == pre->rchild) {
					pre->rchild = cur;
					cur = cur->lchild;
				}
				//恢复pre的右孩子为nullptr
				else {
					pre->rchild = nullptr;
					cout << cur->data << "->";
					cur = cur->rchild;
				}
			}
		}
	}

	//BiTree<T> Parent(BiTree<T> root);
	//BiTree<T> LeftChild(BiTree<T> root);
	//BiTree<T> RightSibling(BiTree<T> root);
	void InsertChild(BiTree<T> root, const T &e)
	{
		if (nullptr == root) {
			root = new BiNode<T>(e);
		}
		else if (e < root->data) {
			InsertChild(root->lchild, e);
		}
		else {
			InsertChild(root->rchild, e);
		}
	}

	void DeleteChild(BiTree<T> root)
	{
		if (nullptr == root) {
			return;
		}
		DeleteChild(root->lchild);
		DeleteChild(root->rchild);
		delete root;
		root = nullptr;
	}

protected:
	//index需要引用类型
	BiTree<T> Create(const T *a, size_t sz, const T &invalid, size_t &index)
	{
		BiTree<T> cur = nullptr;
		if (index < sz && a[index] != invalid) {
			cur = new BiNode<T>(a[index]);
			cur->lchild = Create(a, sz, invalid, ++index);
			cur->rchild = Create(a, sz, invalid, ++index);
		}
		return cur;
	}

	BiTree<T> Copy(BiTree<T> node)
	{
		BiTree<T> cur = nullptr;
		if (nullptr != node) {
			cur = new BiNode<T>(node->data);
			cur->lchild = Copy(node->lchild);
			cur->rchild = Copy(node->rchild);
		}
		return cur;
	}

	//传一级指针的引用
	//void Destroy(BiTree<T>& root)
	//{
	//	if (nullptr != root) {
	//		Destroy(root->lchild);
	//		Destroy(root->rchild);
	//		delete root;
	//		root = nullptr;
	//	}
	//}

	//传二级指针
	void Destroy(BiTree<T>* root)
	{
		if (nullptr != *root) {
			Destroy(&(*root)->lchild);
			Destroy(&(*root)->rchild);
			delete *root;
			*root = nullptr;
		}
	}

	size_t Depth_(BiTree<T> root)
	{
		if (nullptr == root) {
			return 0;
		}
		size_t ld = Depth_(root->lchild);
		size_t rd = Depth_(root->rchild);
		return ld > rd ? ld + 1 : rd + 1;
	}

	size_t Size_(BiTree<T> root)
	{
		if (nullptr == root) {
			return 0;
		}
		return Size_(root->lchild) + Size_(root->rchild) + 1;
	}

	size_t LeafSize_(BiTree<T> root)
	{
		if (nullptr == root) {
			return 0;
		}
		if (nullptr == root->lchild && nullptr == root->rchild)
			return 1;
		return LeafSize_(root->lchild) + LeafSize_(root->rchild);
	}

	void PreorderTraversal_(BiTree<T> root)
	{
		if (root) {
			cout << root->data << " ";
			PreorderTraversal_(root->lchild);
			PreorderTraversal_(root->rchild);
		}
	}

	void InorderTraversal_(BiTree<T> root)
	{
		if (root) {
			InorderTraversal_(root->lchild);
			cout << root->data << " ";
			InorderTraversal_(root->rchild);
		}
	}

	void PostorderTraversal_(BiTree<T> root)
	{
		if (root) {
			PostorderTraversal_(root->lchild);
			PostorderTraversal_(root->rchild);
			cout << root->data << " ";
		}
	}

	void LevelTraversal_(BiTree<T> root)
	{
		if (root) {
			std::queue<BiTree<T>> q;
			q.push(root);
			while (!q.empty()) {
				if (nullptr != q.front()->lchild) {
					q.push(q.front()->lchild);
				}
				if (nullptr != q.front()->rchild) {
					q.push(q.front()->rchild);
				}
				cout << q.front()->data << " ";
				q.pop();
			}
		}
	}
private:
	BiTree<T> m_root;
};


#endif // !BINARY_TREE_H

struct Node {
    int data;
    Node *lchild;
    Node *rchild;
};

int height(Node *cur)
{
    if (!cur) {
        return 0;
    }
    int a = height(cur->lchild);
    int b = height(cur->rchild);
    if (a > b) {
        return a + 1;
    }
    else {
        return b + 1;
    }
}