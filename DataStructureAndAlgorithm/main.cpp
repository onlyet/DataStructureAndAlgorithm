/*
*编译带模版的源码时，出现无法解析的外部符号2019：
*原因：模版在编译的时候不能实例化，没生产obj文件，在main函数只是引用指明入口而已，所以当main函数调用类模版的函数时，会找不到函数的实现
*解决方法：
* (1）在main函数包含#include "template.cpp"，而不要包含#include "template.h"	//只包含源文件，不包含头文件
* (2）在头文件实现类模版的方法	//建议
*/

#include"sequence_list.h"
//#include"sequence_list.cpp"
#if 0
//#include"linked_list.h"
#else
//#include "linked_list_no_header.h"
#include "linked_list_no_header.cpp"
#endif
#include"stack_queue_interview.h"
#include"binary_tree.h"
#include"sort.h"
#include "common.h"

#include<iostream>
#include<string>
#include<time.h>
#include <list>


using namespace std;

void sequence_list_test()
{
	try {
		SequenceList<int> s;
		//s.Clear();
		s.PushBack(2);
		s.PushBack(4);
		s.PushBack(6);
		s.PushBack(7);
		s.PushBack(10);
		s.Print();

		/*	cout << s.Find(100) << endl;
		cout << s.Find(7) << endl;*/

		s.PushBack(6);
		s.PushBack(6);
		s.Remove(7);
		s.Print();
		s.RemoteAll(6);
		s.Print();

		/*	s.Insert(-1, 223);
		s.Erase(5);
		s.Print();

		s.PopBack();
		s.PopBack();
		s.Print();
		s.PushFront(666);
		s.Print();
		s.PopFront();
		s.Print();*/

		//s.Clear();
		/*	s.Destory();
		s.Print();*/
		//cout << s.Length() << endl;
	}
	catch (std::exception e) {
		cout << "exception: " << e.what() << endl;
		//exit(1);
	}
}

void linked_list_test()
{
#if 0
    LinkedList<string> l;
    l.Insert(1, "hello");
    l.Insert(2, "Micheal");
    l.Insert(3, "!");
    l.Print();
    l.PushBack("what");
    l.PushBack("the");
    l.Print();
    string s;
    l.Erase(2, s);
    cout << "erase node :" << s << endl;
    l.Print();
    l.PushFront("one");
    l.Print();
    l.PopFront(s);
    cout << "erase node :" << s << endl;
    l.Print();
    l.PopBack(s);
    l.Print();

    cout << "the length = " << l.Length() << endl;
    cout << "find string at " << l.Find("hello") << endl;
    l.Get(3, s);
    cout << "get string = " << s << endl;
    l.Set(2, "auto");
    l.Print();
    //l.Clear();
    //cout << l.Length() << endl;
    //l.reverse();
    //l.Print();
    l.recursive_reverse(l.Locate(1));
    l.Print();

    LinkedList<int> l;
    l.FrontCreate(5);
    l.Print();
    //LinkedList<int> l2;
    //l2.BackCreate(10);
    //l2.Print();
    l.BubbleSort();
    l.Print();
    l.FindKLast(2);
    int i;
    l.EraseKLast(3, i);
    l.Print();
    l.ReversePrint(l.Head());
    l.InsertBefore(l.Locate(2), 119);
    l.Print();

    LinkedList<int> l, r;
    l.FrontCreate(30);
    r.FrontCreate(20);
    l.Print();
    r.Print();
    LinkedListNode<int> *p = Merge(l.Head(), r.Head());

    Print(p);
#endif

    //int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
#if 0
    LinkedList<int> l(a, 10);
    LinkNode<int>* node =  l.kFromTheBottom(3);
    cout << "k from the bttom data: " << node->data << endl;
    l.print();
    l.reverse();
    l.print();
#endif
#if 0
    LinkedList<int> l;
    l.createWithLoop(a, 10, 3);

    LinkNode<int>* meetPoint = l.loopMeetPoint();
    if (meetPoint) {
        cout << "has loop, meet point data: " << meetPoint->data << endl;

        LinkNode<int>* entryPoint = l.loopEntryPoint(meetPoint);
        if (entryPoint) {
            cout << "entry point data: " << entryPoint->data << endl;
        }
    }
    else {
        cout << "no loop" << endl;
    }
#endif
    // 相交链表这里不在栈上构造，避免析构时结点delete两次。（因为懒得析构两个相交链表）
    LinkedList<int>* l = new LinkedList<int>;
    LinkedList<int>* r = new LinkedList<int>;
    createTwoIntersectingList(*l, *r);
    LinkNode<int>* intersection = getIntersection(*l, *r);
    if (intersection) {
        cout << "intersection data: " << intersection->data << endl;
    }
    else {
        cout << "no intersection" << endl;
    }
}

//#define SORT_NUM 10
//void sort_test()
//{
//	int a[SORT_NUM];
//	srand((unsigned)time(NULL));
//	for (int i = 0; i < SORT_NUM; ++i) {
//		a[i] = rand() % 100;
//	}
//
//	cout << "before sort:" << endl;
//	for (auto &e : a) {
//		cout << e << " ";
//	}
//	cout << endl;
//	BubbleSort(a, SORT_NUM);
//
//	cout << "after sort:" << endl;
//	for (auto &e : a) {
//		cout << e << " ";
//	}
//	cout << endl;
//}

void verify_pop_logic()
{
	StackVerifyPopLogic<int> s;
	s.Input();
	cout << "logic: " << s.Logical() << endl;
	s.Output();
}

void binary_tree_test()
{
    int a[20] = { 1,2,3,'#','#',4,'#','#',5, 6, 7,'#','#','#', 8,'#','#' };
    //int a[10] = { 1, '#', 2 };
    //int a[10] = { 1, '#', '#' };
	BinaryTree<int> b(a, 20, '#');
	cout << "preorder: ";
	b.PreorderTraversal();
	cout << endl;
	//b.Destroy();
	//b.PreorderTraversal();
	//cout << endl;
	/*cout << "inorder: ";
	b.InorderTraversal();
	cout << endl;
	cout << "postorder: ";
	b.PostoederTraversal();
	cout << endl;
	cout << "level traversal: ";
	b.LevelTraversal();
	cout << endl;
	cout << "num of nude: " << b.Size() << endl;
	cout << "depth: " << b.Depth() << endl;
	cout << "num of leaf: " << b.LeafSize() << endl;

	cout << "non recursive preorder: ";
	b.NonRecursivePreorder();
	cout << endl;
	cout << "non recursive inorder: ";
	b.NonRecursiveInorder();
	cout << endl;
	cout << "non recursive postorder: ";
	b.NonRecursivePostorder();
	cout << endl;

	cout << "non recursive preorder v2: ";
	b.NonRecursivePreorder_v2();
	cout << endl;

	cout << "non recursive preorder space complexity O(1): ";
	b.NonRecursivePreorder_O1();
	cout << endl;*/
	//cout << "non recursive inorder space complexity O(1): ";
	//b.NonRecursiveInorder_O1();
	//cout << endl;

    cout << "depth of bitree is : " << b.Depth() << endl;
    cout << "leaf size of bitree is : " << b.LeafSize() << endl;
}

void sort_test()
{
#if 0
    //int a[10] = { 15, 3, 7, 42, 1, 26, 8, 84, 99, 10 };
    int a[20] = { 18, 162, 83, 20, 198, 40, 230, 227, 289, 105, 76, 236, 173, 276, 192, 277, 85, 169, 52, 216 };
    int tmp[10] = { 0 };
#else
    int len = 20;
    int* a = new int[len];
    srand(time(NULL));
    for (int i = 0; i < len; ++i) {
        a[i] = rand() % 400;
    }
#endif
    cout << "Before sorted:";
    //for (auto &e : a) {
    //    cout << e << " ";
    //}
    for (int i = 0; i < len; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;

    //bubble_sort_3(a, 10);
    //selection_sort(a, 10);
    //insertion_sort(a, 10);
    //shell_sort(a, 10);
    //quick_sort(a, 0, 9);
    //quick_sort(a, 10);
    //merge_sort(a, 0, 9, tmp);
    //merge_sort(a, 10, tmp);

    //heap_sort(a, 10);
    //counting_sort_demo(a, 10);
    //BucketSort(10, a);

    //bucket_sort(a, 20);
    radix_sort(a, len);

    cout << " After sorted:";
    //for (auto &e : a) {
    //    cout << e << " ";
    //}
    for (int i = 0; i < len; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main()
{
	
	try {
		linked_list_test();

		//sort_test();

		//verify_pop_logic();

		//binary_tree_test();

        //sort_test();

        kmp_test();

	}
	catch (std::exception &e) {
		cout << e.what() << endl;
	}
    system("pause");
	return 0;
}