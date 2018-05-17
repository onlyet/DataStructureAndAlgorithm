/*
 *编译带模版的源码时，出现无法解析的外部符号2019：
 *原因：模版在编译的时候不能实例化，没生产obj文件，在main函数只是引用指明入口而已，所以当main函数调用类模版的函数时，会找不到函数的实现
 *解决方法：
 * (1）在main函数包含#include "template.cpp"，而不要包含#include "template.h"	//只包含源文件，不包含头文件
 * (2）在头文件实现类模版的方法	//建议
*/

#include"sequence_list.h"
//#include"sequence_list.cpp"
#include"linked_list.h"

#include<iostream>
#include<string>

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
}

int main()
{
	
	linked_list_test();

	system("pause");
	return 0;
}