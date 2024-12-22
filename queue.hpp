#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

/**
 * Класс queue<T>, наследник от list<T>
 * Реализует функционал "очередь" (FIFO).
 */
template <typename T>
class queue : public list<T>
{
    using node = typename list<T>::node;

private:
    node*  front_; // начало очереди
    node*  back_;  // конец очереди
    size_t size_;

protected:
    /**
     * Переопределение защищённого виртуального метода Print(...)
     * для оператора <<
     */
    void Print(std::ostream& os) const override
    {
        node* curr = front_;
        while (curr)
        {
            os << curr->data;
            if (curr->next)
                os << "->";
            curr = curr->next;
        }
    }

public:
    // Конструктор по умолчанию — пустая очередь
    queue()
        : front_(nullptr), back_(nullptr), size_(0)
    {}

    // Конструктор копирования
    queue(const queue<T>& other)
        : front_(nullptr), back_(nullptr), size_(0)
    {
        *this = other; // вызов собственного operator=
    }

    // Конструктор перемещения
    queue(queue<T>&& other) noexcept
        : front_(other.front_), back_(other.back_), size_(other.size_)
    {
        other.front_ = nullptr;
        other.back_  = nullptr;
        other.size_  = 0;
    }

    // Деструктор
    ~queue()
    {
        while (!IsEmpty())
            Pop();
    }

    //------------------------------------------------------
    //    ОПЕРАТОРЫ ПРИСВАИВАНИЯ
    //------------------------------------------------------

    /**
     * Присваивание из базового класса (виртуальное).
     * Проверяем, действительно ли другой объект — это queue<T>.
     */
    list<T>& operator=(const list<T>& other) override
    {
        if (this == &other)
            return *this;

        // Пытаемся привести к queue<T>
        const queue<T>* otherQ = dynamic_cast<const queue<T>*>(&other);
        if (otherQ)
        {
            // Если это действительно queue<T>, копируем, сохранив FIFO-порядок.
            while (!IsEmpty())
                Pop();

            // Единственный проход по цепочке otherQ->front_, добавляем Push(...)
            for (node* curr = otherQ->front_; curr; curr = curr->next)
            {
                Push(curr->data);
            }
        }
        else
        {
            // Иначе — это stack<T> или другой наследник list<T>.
            throw std::runtime_error(
                "queue::operator=(list<T>&): пытаемся присвоить queue из НЕ queue."
            );
        }
        return *this;
    }

    /**
     * Оператор присваивания из собственного типа (queue<T>).
     */
    queue<T>& operator=(const queue<T>& other)
    {
        if (this == &other)
            return *this;

        // Очистим текущую очередь
        while (!IsEmpty())
            Pop();

        // За один проход копируем элементы: front_ -> back_
        for (node* curr = other.front_; curr; curr = curr->next)
        {
            Push(curr->data);
        }
        return *this;
    }

    /**
     * Оператор присваивания по перемещению (из своего же типа).
     */
    queue<T>& operator=(queue<T>&& other) noexcept
    {
        if (this == &other)
            return *this;

        // Очистим текущие данные
        while (!IsEmpty())
            Pop();

        front_ = other.front_;
        back_  = other.back_;
        size_  = other.size_;

        other.front_ = nullptr;
        other.back_  = nullptr;
        other.size_  = 0;

        return *this;
    }

    //------------------------------------------------------
    //   РЕАЛИЗАЦИЯ АБСТРАКТНЫХ МЕТОДОВ ОЧЕРЕДИ
    //------------------------------------------------------

    // Добавляем в хвост очереди
    void Push(const T& value) override
    {
        node* newNode = new node(value);
        if (IsEmpty())
        {
            front_ = newNode;
            back_  = newNode;
        }
        else
        {
            back_->next = newNode;
            back_       = newNode;
        }
        ++size_;
    }

    // Удаляем из головы
    void Pop() override
    {
        if (IsEmpty())


throw std::underflow_error("queue::Pop(): очередь пуста!");

        node* temp = front_;
        front_ = front_->next;
        delete temp;
        --size_;

        if (size_ == 0)
            back_ = nullptr;
    }

    // Посмотреть элемент в голове (не удаляя)
    T GetFront() const override
    {
        if (IsEmpty())
            throw std::underflow_error("queue::GetFront(): очередь пуста!");
        return front_->data;
    }

    // Проверка на пустоту
    bool IsEmpty() const override
    {
        return (size_ == 0);
    }

    // Возвращает размер очереди
    size_t Size() const override
    {
        return size_;
    }
};

#endif // QUEUE_HPP
