#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <stdexcept>

/**
 * Абстрактный шаблонный класс "односвязный список",
 * переименован в "list" по требованию.
 */
template <typename T>
class list
{
protected:
    /**
     * Внутренний узел (node).
     * Защищён, т. к. используется потомками (stack / queue).
     */
    struct node
    {
        T data;
        node* next;

        node(const T& value, node* nextPtr = nullptr)
            : data(value), next(nextPtr) {}
    };

    /**
     * Защищённый виртуальный метод печати —
     * вызывается в operator<< для вывода списка.
     */
    virtual void Print(std::ostream& os) const = 0;

public:
    /// Виртуальный деструктор
    virtual ~list() = default;

    // Абстрактные методы
    virtual void   Push(const T& value) = 0;
    virtual void   Pop()               = 0;
    virtual T      GetFront()    const = 0;
    virtual bool   IsEmpty()     const = 0;
    virtual size_t Size()        const = 0;

    /**
     * Виртуальная операция присваивания из ссылки на базовый класс "list".
     * Нужно, чтобы можно было делать что-то вроде:
     *   stack<int> s;
     *   list<int>& ref = s;
     *   queue<int> q;
     *   q = ref;  // Здесь используется именно этот оператор=
     */
    virtual list<T>& operator=(const list<T>& other) = 0;

    /**
     * Перегрузка оператора вывода <<:
     * внутри вызывает Print(...).
     */
    friend std::ostream& operator<<(std::ostream& os, const list<T>& l)
    {
        l.Print(os);
        return os;
    }

    /**
     * Перегрузка оператора ввода >>:
     * внутри вызывает Push(...) для одного считанного элемента.
     */
    friend std::istream& operator>>(std::istream& is, list<T>& l)
    {
        T value;
        is >> value;
        l.Push(value);
        return is;
    }
};

#endif // LIST_HPP
