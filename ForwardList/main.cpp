#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------\n"

class Element
{
	int Data;		
	Element* pNext;	
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
int Element::count = 0;

class ForwardList
{
	Element* Head;	
	int size;
public:
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	//ForwardList(int size)
	//{
	//	for (int i = 0; i < size; ++i)
	//	{
	//		push_back(0);  // заполним списком нулевыми значениями
	//	}
	//	cout << "LSConstructor:\t" << this << endl;
	//}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	void insert(int Data, int Index)
	{
		if (Index == 0) return push_front(Data);
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}
		New->pNext = Temp->pNext;
		Temp->pNext = New;

		size++;
	}
	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;

		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void erase(int Index)
	{
		if (Index == 0) return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) {
			Temp = Temp->pNext;
		}
		Element* ToDelete = Temp->pNext;
		Temp->pNext = ToDelete->pNext;
		size--;
	}


	//				Methods:
	void print()const
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количество элементов списка:" << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}

	/*int get_size(int size)const
	{
		size = this -> size;
		return size;
	}*/
};

//#define BASE_CHECK
//#define SIZE_CHECK
//#define HOME_WORK_1

void main()
{
	setlocale(LC_ALL, "");
	cout << "Hello ForwardList" << endl;

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.pop_front();
	//list.pop_back();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.erase(index);
	list.print();
#endif // BASE_CHECK

#ifdef SIZE_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();
#endif // SIZE_CHECK

#ifdef HOME_WORK_1
	ForwardList list(5);
	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif // HOME_WORK_1


}