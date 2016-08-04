// Janak Jobanputra and Chirag Kashyap

#include "CPUTimer.h"
//#include "LinkedList.cpp"
//#include "StackAr.cpp"
#include "dsexceptions.h"
//#include "CursorList.cpp"
#include "LinkedList.h"
#include "StackAr.h"
#include "CursorList.h"
//#include "QueueAr.cpp"
//#include "StackLi.cpp"
//#include "vector.cpp"
#include "QueueAr.h"
#include "StackLi.h"
#include "vector.h"
#include "SkipList.h"
#include <string.h>
#include <iostream>
#include <fstream>
//#include "SkipList.cpp"
#define MAX_SIZE 250000
vector<CursorNode <int> > cursorSpace(250000);

using namespace std;

int getChoice()
{
	int choice=0;

	cout << endl;
	cout << "      ADT Menu" << endl;
	cout << "0.	Quit" << endl;
	cout << "1.	List" << endl;
	cout << "2.	Cursor List" << endl;
	cout << "3.	Stack Array" << endl;
	cout << "4.	Stack List" << endl;
	cout << "5.	Queue Array" << endl;
	cout << "6.	Skip List" << endl;
	cout << " Your choice >> ";
	cin >> choice;
	return choice;
}

void RunList(char* filename)
{
	string dump;
	char space, c;
	int num;
	List<int> list;
	ListItr<int> i=list.zeroth();

	ifstream inf(filename);
	getline(inf, dump);
	while(inf >> c >> num)
	{
		if( c == 'i')
		{
			list.insert(num, i);
		}
		else if( c == 'd')
		{
			list.remove(num);
		}
		//cout << c << num << " ";
	}

}


void RunCursorList(char* filename)
{
	string dump;
	char space, c;
	int num;
	CursorList<int> cursor(cursorSpace);
	CursorListItr<int> i=cursor.zeroth();

	ifstream inf(filename);
	getline(inf, dump);
	while(inf >> c >> num)
	{
		if( c == 'i')
		{
			cursor.insert(num, i);
		}
		else if( c == 'd')
		{
			cursor.remove(num);
		}
		//cout << c << num << " ";
	}
	
}


void RunStackAr(char* filename)
{
	string dump;
	char space, c;
	int num;
	StackAr<int> stackArray(MAX_SIZE);
	//CursorListItr<int> i=cursor.zeroth();

	ifstream inf(filename);
	getline(inf, dump);
	while(inf >> c >> num)
	{
		if( c == 'i')
		{
			stackArray.push(num);
		}
		else if( c == 'd')
		{
			stackArray.pop();
		}
		//cout << c << num << " ";
	}
}


void RunStackLi(char* filename)
{
	string dump;
	char space, c;
	int num;
	StackLi<int> stackList;
	//CursorListItr<int> i=cursor.zeroth();

	ifstream inf(filename);
	getline(inf, dump);
	while(inf >> c >> num)
	{
		if( c == 'i')
		{
			stackList.push(num);
		}
		else if( c == 'd')
		{
			stackList.pop();
		}
		//cout << c << num << " ";
	}
}


void RunQueueAr(char* filename)
{
	string dump;
	char space, c;
	int num;
	Queue<int> q(MAX_SIZE);

	ifstream inf(filename);
	getline(inf, dump);
	while(inf >> c >> num)
	{
		if( c == 'i')
		{
			q.enqueue(num);
		}
		else if( c == 'd')
		{
			q.dequeue();
		}
		//cout << c << num << " ";
	}
}


void RunSkipList(char* filename)
{
	string dump;
	char space, c;
	int num;
	SkipList<int> skip(0, MAX_SIZE);

	ifstream inf(filename);
	getline(inf, dump);
	while(inf >> c >> num)
	{
		if( c == 'i')
		{
			skip.insert(num);
		}
		else if( c == 'd')
		{
			skip.deleteNode(num);
		}
		//cout << c << num << " ";
	}
}


int main()
{
	int choice = 0;
	CPUTimer ct;
	char filename[100];
	cout << "Filename >> ";
	cin >> filename;

	do
	{
		choice = getChoice();
		ct.reset();
		switch(choice)
		{
			case 1: RunList(filename); break;
			case 2: RunCursorList(filename); break;
			case 3: RunStackAr(filename); break;
			case 4: RunStackLi(filename); break;
			case 5: RunQueueAr(filename); break;
			case 6: RunSkipList(filename); break;
		}
		cout << "CPU time: " << ct.cur_CPUTime() << endl;
	}while(choice > 0);
	//cout << "Filename is " << filename << endl;
	//cout << "Choice is " << choice << endl;
	return 0;
}