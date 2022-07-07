#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <string>

// Класс, описывающая один елемент (узел)
template <typename T>
class Element
{
public:
    T data;           // Данные
    Element<T> *next; // Адрес следующего элемента в списке
    Element<T> *prev; // Адрес предыдущего элемента в списке

    Element<T>(T Data) : data(Data), next(nullptr), prev(nullptr)
    {
    } // Конструктор
};

// Класс, реализующий двусвязный список
template <class T>
class List
{
private:
    Element<T> *head; // Указатель на первый элемент списка
    Element<T> *tail; // Указатель на последний элемент списка
    int count;        // Количество элементов в списке

public:
    // Конструктор
    List();

    // Деструктор
    //~List();

    Element<T> *GetFirst();                  // Получить первый элемент
    Element<T> *GetLast();                   // Получить последний элемент
    Element<T> *Move(int index);             // Переместиться на элемент по индексу
    int GetCount();                          // Получить количество элементов
    void AddEnd(T _data);                    // Добавить элемент в конец списка
    void AddBegin(T _data);                  // Добавить элемент в начало списка
    void SetElement(T _data, Element<T> *t); // Изменить значение элемента в текущей позиции
    void Delete(Element<T> *item);           // Удалить текущий элемент
    void Clear();                            // Очистка списка
};

// Конструктор создаёт пустой список
template <class T>
List<T>::List()
{
    head = tail = nullptr;
    count = 0;
}

/*
// Деструктор
template <class T>
List<T>::~List()
{
Clear(); // очистить список
}
*/

// Получить количество элементов
template <class T>
int List<T>::GetCount()
{
    return count;
}


// Получить первый элемент
template <class T>
Element<T> *List<T>::GetFirst()
{
    return head;
}

// Получить последний элемент
template <class T>
Element<T> *List<T>::GetLast()
{
    return tail;
}

// Переместиться на элемент по индексу
template <class T>
Element<T> *List<T>::Move(int index)
{
    if (index < count && index >= 0)
    {
        Element<T> *t;
        int middle = count / 2; // Устанавливаем центр для эффективного перемещения
        if (index < middle)
        {
            t = head;
            for (int i = 0; i < index; i++)
                t = t->next;
            return t;
        }
        else
        {
            t = tail;
            for (int i = count - 1; i > index; i--)
                t = t->prev;
            return t;
        }
    }
    else
        std::cout << "Out of range ERROR" << std::endl;
    return tail;
}

// Добавить элемент в конец списка
template <class T>
void List<T>::AddEnd(T _data)
{
    try
    {

        Element<T> *t = new Element<T>(_data); // Создать новый элемент с данными _data
        t->prev = tail;                        // установить указатель на предыдущий элемент

        if (tail != nullptr) // Заполнить поле переставить указатель последнего элемента на новый
            tail->next = t;

        if (count == 0) // Проверка, есть ли в списке элементы
        {
            // Если элементов нет, установить элемент на начало и конец
            head = tail = t;
        }
        else
        {
            tail = t; // если элементы в списке есть, то это конец списка
        }

        count++; // Увеличить общее количество элементов
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << e.what(); // Если память не выделена, то вывести системное сообщение
    }
}

// Добавить элемент в начало списка
template <class T>
void List<T>::AddBegin(T _data)
{
    try
    {
        Element<T> *t = new Element<T>(_data); // Создание нового элемента
        t->next = head;                        // следующий элемент указывает на предыдущий первый

        if (count > 0) // Проверка, не пустой ли список
        {
            head->prev = t;
            head = t;
        }
        else // если элементов нет, то устанавливаем элемент на начало и конец
            head = tail = t;

        count++; // Увеличение общего количества элементов
    }
    catch (const std::bad_alloc &e) // если память не выделена, ошибка
    {
        std::cerr << e.what();
    }
}

// Изменить значение элемента в текущей позиции
template <class T>
void List<T>::SetElement(T _data, Element<T> *t)
{
    t->data = _data;
}

// Удалить текущий элемент
template <class T>
void List<T>::Delete(Element<T> *item)
{
    if (count == 0) // Проверка, не пустой ли список
        return;

    Element<T> *itemPrev = item->prev; // Предыдущий элемент
    Element<T> *itemNext = item->next; // Следующий элемент

    if ((count > 1) && (itemPrev != nullptr)) // Проверка, удаляется ли не первый элемент списка
        itemPrev->next = itemNext;

    if ((count > 1) && (itemNext != nullptr)) // Проверка, удаляется ли не последний элемент списка
        itemNext->prev = itemPrev;

    if (item == head) // Если удаляется первый элемент
        head = itemNext;

    if (item == tail) // Если удаляется последний элемент
        tail = itemPrev;

    delete item; // Удалить элемент item

    count--; // Уменьшить общее количество элементов
}

// Очистка списка
template <class T>
void List<T>::Clear()
{
    if (count != 0)
    {
        int c = count;
        for (int i = 0; i < c; i++)
            Delete(head);
    }
}
#endif // LIST_H
