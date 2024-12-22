#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"

/**
 * Класс stack<T>, наследник от list<T>
 * Реализует функционал "стек" (LIFO).
 */
template <typename T>
class stack : public list<T>
{
    using node = typename list<T>::node;

private:
    node*   head_;  // Указатель на верхний (первый) элемент стека
    size_t  size_;  // Текущее число элементов в стеке

protected:
    /**
     * Переопределение защищённого виртуального метода Print(...)
     * для оператора <<
     */
    void Print(std::ostream& os) const override
    {
        node* curr = head_;
        while (curr)
        {
            os << curr->data;
            if (curr->next)
                os << "->";
            curr = curr->next;
        }
    }

public:
    // Конструктор по умолчанию — пустой стек
    stack()
        : head_(nullptr), size_(0)
    {}

    // Конструктор копирования
    stack(const stack<T>& other)
        : head_(nullptr), size_(0)
    {
        *this = other;  // вызов собственного operator=
    }

    // Конструктор перемещения
    stack(stack<T>&& other) noexcept
        : head_(other.head_), size_(other.size_)
    {
        other.head_ = nullptr;
        other.size_ = 0;
    }

    // Деструктор
    ~stack()
    {
        while (!IsEmpty())
        {
            Pop();
        }
    }

    //------------------------------------------------------
    //    ОПЕРАТОРЫ ПРИСВАИВАНИЯ
    //------------------------------------------------------

    /**
     * Присваивание из базового класса (виртуальное).
     * Проверяем, действительно ли другой объект — это stack<T>.
     */
    list<T>& operator=(const list<T>& other) override
    {
        if (this == &other)
            return *this;

        // Пытаемся привести к stack<T>
        const stack<T>* otherStack = dynamic_cast<const stack<T>*>(&other);
        if (otherStack)
        {
            // Если это действительно stack<T>, копируем.
            // Сначала очистим свой стек.
            while (!IsEmpty())
                Pop();

            // Копируем элементы, чтобы итоговый стек имел такой же порядок, как у otherStack.
            // Но простой Push(...) на пустой будет инвертировать (т.к. вершина станет "концом").
            // Поэтому делаем "двойной разворот" через временный список.

            // 1) tempHead = обратный список
            node* tempHead = nullptr;
            for (node* curr = otherStack->head_; curr; curr = curr->next)
            {
                node* newNode = new node(curr->data, tempHead);
                tempHead = newNode;
            }
            // 2) Разворачиваем tempHead обратно в head_
            node* reversed = nullptr;
            while (tempHead)
            {
                node* next = tempHead->next;
                tempHead->next = reversed;
                reversed = tempHead;
                tempHead = next;
            }
            head_ = reversed;

            // Считаем размер
            size_ = 0;
            node* sizeCounter = head_;
            while (sizeCounter)
            {
                ++size_;
                sizeCounter = sizeCounter->next;
            }
        }
        else
        {
            // Иначе — это queue<T> или другой наследник list<T>.
            // По задаче выбрасываем исключение (либо можно придумать логику "конвертации").
            throw std::runtime_error(
                "stack::operator=(list<T>&): пытаемся присвоить stack из НЕ stack."
            );
        }

        return *this;
    }

    /**
     * Оператор присваивания из собственного типа (stack<T>).
     * Здесь всё проще: никакого dynamic_cast.
     */
    stack<T>& operator=(const stack<T>& other)
    {
        if (this == &other)
            return *this;

        // Очистим текущий стек
        while (!IsEmpty())
            Pop();

        // "Двойной разворот", чтобы порядок элементов сохранился.
        node* tempHead = nullptr;
        for (node* curr = other.head_; curr; curr = curr->next)
        {
            node* newNode = new node(curr->data, tempHead);
            tempHead = newNode;


}
        node* reversed = nullptr;
        while (tempHead)
        {
            node* next = tempHead->next;
            tempHead->next = reversed;
            reversed = tempHead;
            tempHead = next;
        }
        head_ = reversed;

        // Подсчитываем размер
        size_ = 0;
        node* sizeCounter = head_;
        while (sizeCounter)
        {
            ++size_;
            sizeCounter = sizeCounter->next;
        }
        return *this;
    }

    /**
     * Оператор присваивания по перемещению (из своего же типа).
     */
    stack<T>& operator=(stack<T>&& other) noexcept
    {
        if (this == &other)
            return *this;

        // Очистим текущий
        while (!IsEmpty())
            Pop();

        head_ = other.head_;
        size_ = other.size_;

        other.head_ = nullptr;
        other.size_ = 0;

        return *this;
    }

    //------------------------------------------------------
    //   РЕАЛИЗАЦИЯ АБСТРАКТНЫХ МЕТОДОВ СТЕКА
    //------------------------------------------------------

    // Поместить элемент на верх стека
    void Push(const T& value) override
    {
        node* newNode = new node(value, head_);
        head_ = newNode;
        ++size_;
    }

    // Удалить элемент с вершины
    void Pop() override
    {
        if (IsEmpty())
            throw std::underflow_error("stack::Pop(): стек пуст!");

        node* temp = head_;
        head_ = head_->next;
        delete temp;
        --size_;
    }

    // Взять значение с вершины (не удаляя)
    T GetFront() const override
    {
        if (IsEmpty())
            throw std::underflow_error("stack::GetFront(): стек пуст!");
        return head_->data;
    }

    // Проверка на пустоту
    bool IsEmpty() const override
    {
        return (size_ == 0);
    }

        // Размер стека
        size_t Size() const override
        {
            return size_;
        }
    };

    #endif // STACK_HPP
