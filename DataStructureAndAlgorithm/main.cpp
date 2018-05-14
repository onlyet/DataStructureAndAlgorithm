#include"sequence_list.h"
#include<iostream>

using namespace std;

int main()
{
	try {
		SequenceList<int> s;
		s.Clear();
	/*	s.PushBack(2);
		s.PushBack(4);
		s.PushBack(6);
		s.PushBack(7);
		s.PushBack(10);
		s.Print();*/

	}
	catch (std::exception e) {
		cout << "exception: " << e.what() << endl;
		//exit(1);
	}

	system("pause");
	return 0;
}