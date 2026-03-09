#include <iostream>
#include <ctime>
#include <iterator>

using namespace std;

template<typename T>
class Element
{
    T Data;           // Значение элемента
    Element<T>* pNext; // Указатель на следующий элемент
    static int count;
public:
    Element(T data, Element<T>* next = nullptr) : Data(data), pNext(next)
    {
        count++;
#ifdef DEBUG
        cout << "EConstructor:\t" << this << endl;
#endif
    }
    ~Element()
    {
        count--;
#ifdef DEBUG
        cout << "EDestructor:\t" << this << endl;
#endif
    }
    friend class ForwardList<T>;
    friend class Iterator<T>;
    friend class ConstIterator<T>;
    template<typename U>
    friend ForwardList<U> operator+(const ForwardList<U>& left, const ForwardList<U>& right);
};

template<typename T>
int Element<T>::count = 0;

template<typename T>
class Iterator
{
    Element<T>* temp;
public:
    Iterator(Element<T>* t = nullptr) :temp(t)
    {
        cout << "ItConstructor:\t" << this << endl;
    }
    ~Iterator()
    {
        cout << "ItDestructor:\t" << this << endl;
    }
    Iterator& operator++()
    {
        temp = temp->pNext;
        return *this;
    }
    Iterator operator++(int)
    {
        Iterator old = *this;
        temp = temp->pNext;
        return old;
    }
    bool operator==(const Iterator& other) const
    {
        return this->temp == other.temp;
    }
    bool operator!=(const Iterator& other) const
    {
        return this->temp != other.temp;
    }
    T& operator*()
    {
        return temp->Data;
    }
};

template<typename T>
class ConstIterator
{
    Element<T>* temp;
public:
    ConstIterator(Element<T>* t = nullptr) :temp(t)
    {
        cout << "ItConstructor:\t" << this << endl;
    }
    ~ConstIterator()
    {
        cout << "ItDestructor:\t" << this << endl;
    }
    ConstIterator& operator++()
    {
        temp = temp->pNext;
        return *this;
    }
    ConstIterator operator++(int)
    {
        ConstIterator old = *this;
        temp = temp->pNext;
        return old;
    }
    bool operator==(const ConstIterator& other) const
    {
        return this->temp == other.temp;
    }
    bool operator!=(const ConstIterator& other) const
    {
        return this->temp != other.temp;
    }
    const T& operator*() const
    {
        return temp->Data;
    }
};

template<typename T>
class ForwardList
{
    Element<T>* head;      // Голова списка
    int size;
public:
    using iterator = Iterator<T>;
    using const_iterator = ConstIterator<T>;

    Element<T>* get_head() const
    {
        return head;
    }
    int get_size() const
    {
        return size;
    }
    const_iterator begin() const
    {
        return head;
    }
    const_iterator end() const
    {
        return nullptr;
    }
    iterator begin()
    {
        return head;
    }
    iterator end()
    {
        return nullptr;
    }

    // Constructors:
    ForwardList()
    {
        head = nullptr;
        size = 0;
        cout << "LConstructor:\t" << this << endl;
    }
    explicit ForwardList(int s) : ForwardList()
    {
        while (s--) push_front(static_cast<T>(0));
        cout << "1argLConstructor:\t" << this << endl;
    }
    ForwardList(std::initializer_list<T> il) : ForwardList()
    {
        for (auto it = il.begin(); it != il.end(); ++it)
        {
            push_back(*it);
        }
    }
    ForwardList(const ForwardList<T>& other) : ForwardList()
    {
        *this = other;
        cout << "LCopyConstructor:\t" << this << endl;
    }
    ForwardList(ForwardList<T>&& other) : ForwardList()
    {
        *this = std::move(other);
        cout << "LMoveConstructor:\t" << this << endl;
    }
    ~ForwardList()
    {
        while (head) pop_front();
        cout << "LDestructor:\t" << this << endl;
    }

    // Operators:
    ForwardList<T>& operator=(const ForwardList<T>& other)
    {
        if (this == &other) return *this;
        while (head) pop_front();
        for (Element<T>* temp = other.head; temp; temp = temp->pNext)
            push_front(temp->Data);
        reverse();
        cout << "LCopyAssignment:\t" << this << endl;
        return *this;
    }
    ForwardList<T>& operator=(ForwardList<T>&& other)
    {
        if (this == &other) return *this;
        while (head) pop_front();
        this->head = other.head;
        this->size = other.size;
        other.head = nullptr;
        other.size = 0;
        cout << "LMoveAssignment:\t" << this << endl;
        return *this;
    }
    T& operator[](int index)
    {
        Element<T>* temp = head;
        for (int i = 0; i < index; i++) temp = temp->pNext;
        return temp->Data;
    }

    // Adding elements:
    void push_front(T data)
    {
        head = new Element<T>(data, head);
        size++;
    }
    void push_back(T data)
    {
        if (!head) return push_front(data);
        Element<T>* temp = head;
        while (temp->pNext) temp = temp->pNext;
        temp->pNext = new Element<T>(data);
        size++;
    }
    void insert(T data, int index)
    {
        if (index == 0) return push_front(data);
        Element<T>* temp = head;
        for (int i = 0; i < index - 1 && temp->pNext; i++) temp = temp->pNext;
        temp->pNext = new Element<T>(data, temp->pNext);
        size++;
    }

    // Removing elements:
    void pop_front()
    {
        Element<T>* erased = head;
        head = head->pNext;
        delete erased;
        size--;
    }
    void pop_back()
    {
        Element<T>* temp = head;
        while (temp->pNext->pNext) temp = temp->pNext;
        delete temp->pNext;
        temp->pNext = nullptr;
        size--;
    }

    // Methods:
    void reverse()
    {
        ForwardList<T> reversed;
        while (head)
        {
            reversed.push_front(head->Data);
            pop_front();
        }
        this->head = reversed.head;
        reversed.head = nullptr;
    }
    void print() const
    {
        for (Element<T>* temp = head; temp; temp = temp->pNext)
            cout << temp << '\t' << temp->Data << '\t' << temp->pNext << endl;
        cout << "Количество элементов списка: " << size << endl;
        cout << "Общее количество элементов: " << Element<T>::count << endl;
    }
};

template<typename T>
ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
    ForwardList<T> result = left;
    for (typename ForwardList<T>::const_iterator it = right.begin(); it != right.end(); ++it)
        result.push_back(*it);
    return result;
}

// Макросы, используемые ранее
#define tab "\t"
#define delimiter "\n-----------------------------------------\n"

// Основная программа
int main()
{
    setlocale(LC_ALL, "");
    cout << "Hello ForwardList" << endl;

#ifdef BASE_CHECK
    int n;
    cout << "Введите размер списка: "; cin >> n;
    ForwardList<int> list;
    for (int i = 0; i < n; i++)
    {
        list.push_back(rand() % 100);
    }
    list.print();
#endif // BASE_CHECK

#ifdef SIZE_CHECK
    ForwardList<int> list1;
    list1.push_back(3);
    list1.push_back(5);
    list1.push_back(8);
    list1.push_back(13);
    list1.push_back(21);

    ForwardList<int> list2;
    list2.push_back(34);
    list2.push_back(55);
    list2.push_back(89);

    list1.print();
    list2.print();
#endif // SIZE_CHECK

#ifdef HOME_WORK_1
    ForwardList<int> list(5);
    list.print();
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

#ifdef COPY_SEMANTIC_CHECK
    ForwardList<int> list1;
    list1.push_back(3);
    list1.push_back(5);
    list1.push_back(8);
    list1.push_back(13);
    list1.push_back(21);
    list1 = list1;
    list1.print();

    ForwardList<int> list2 = list1; // CopyConstructor
    list2.print();

    list2 = list1;                  // CopyAssignment
    list2.print();
#endif // COPY_SEMANTIC_CHECK

#ifdef PERFORMANCE_CHECK
    int n;
    cout << "Введите размер списка: "; cin >> n;
    ForwardList<int> list1;
    clock_t start = clock();
    for (int i = 0; i < n; i++)
    {
        list1.push_front(rand() % 100);
    }
    clock_t end = clock();
    cout << delimiter << endl;
    cout << "list1 заполнен за " << double(end - start) / CLOCKS_PER_SEC << " секунд" << endl;
    cout << delimiter << endl;

    start = clock();
    ForwardList<int> list2 = list1;
    end = clock();
    cout << delimiter << endl;
    cout << "list2 скопирован за " << double(end - start) / CLOCKS_PER_SEC << " секунд" << endl;
    cout << delimiter << endl;
#endif // PERFORMANCE_CHECK

#ifdef MOVE_SEMANTIC_CHECK
    ForwardList<int> list1;
    list1.push_back(3);
    list1.push_back(5);
    list1.push_back(8);
    list1.push_back(13);
    list1.push_back(21);

    ForwardList<int> list2;
    list2.push_back(34);
    list2.push_back(55);
    list2.push_back(89);

    cout << delimiter << endl;
    ForwardList<int> list3 = list1 + list2;
    cout << delimiter << endl;
    list3.print();
#endif // MOVE_SEMANTIC_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
    int arr[] = { 3, 5, 8, 13, 21 };
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        cout << arr[i] << tab;
    }
    cout << endl;

    for (int i : arr)
    {
        cout << i << tab;
    }
    cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
    ForwardList<int> list = { 3, 5, 8, 13, 21 };
    for (int i : list)
    {
        cout << i << tab;
    }
    cout << endl;

    for (typename ForwardList<int>::iterator it = list.begin(); it != list.end(); ++it)
    {
        cout << *it << tab;
    }
    cout << endl;
#endif // RANGE_BASED_FOR_LIST

    ForwardList<int> list1 = { 3, 5, 8, 13, 21 };
    ForwardList<int> list2 = { 34, 55, 89 };
    ForwardList<int> list3 = list1 + list2;
    for (int i : list1) cout << i << tab; cout << endl;
    for (int i : list2) cout << i << tab; cout << endl;
    for (int i : list3) cout << i << tab; cout << endl;

    uint8_t ui8t = 49;
    cout << static_cast<int>(ui8t) << endl;

    return 0;
}