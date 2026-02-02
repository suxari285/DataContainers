#include<iostream>

using std::cin;
using std::cout;
using std::endl;

#define delimetr "\n----------------------------------\n"
#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t:" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
};

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	void push_front(int Data)
	{
		//1)Создаём добавляемый элемент
		Element* New = new Element(Data);
		New->
	}
};

void main()
{
	setlocale(LC_ALL, "");
	cout << "Hello ForwardList" << endl;
	ForwardList list;
}