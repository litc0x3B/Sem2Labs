#pragma once
#include <functional>
#include "sequence/sequence.hpp"
#include "sequence/linkedListSequence.hpp"

template<class T, template<class> class SequenceType = LinkedListSequence>
class MyDeque
{
private:
    Sequence<T> *sequence;
public:
    MyDeque();
    MyDeque(const MyDeque<T, SequenceType> &deque);
    MyDeque(const T *arr, int size);

    ~MyDeque();

    int GetSize() const;
    bool isEmpty() const;
    T Back() const;
    T Front() const;
    T Reduce(const std::function<T(T prev, T current)> &func) const;
    int Find(const MyDeque<T, SequenceType> &deque, int startIndex = 0) const;

    void PushBack(T item);
    void PushFront(T item);
    void PopBack();
    void PopFront();
    void Map(const std::function<void(T&)> &func);
    void Map(const std::function<void(T&)> &func, int startIndex, int endIndex);

    MyDeque<T, SequenceType> operator=(const MyDeque<T, SequenceType> &deque);
    T &operator[](int index);

    MyDeque<T, SequenceType> Where(const std::function<bool(T)> &func) const;
    MyDeque<T, SequenceType> GetSubsequence(int startIndex, int endIndex) const;
    MyDeque<T, SequenceType> Concat(const MyDeque<T, SequenceType> &deque) const;
};

template<class T, template<class> class SequenceType>
MyDeque<T, SequenceType>::MyDeque()
{
    static_assert(std::is_base_of<Sequence<T>, SequenceType<T>>(), "SequenceType is not derived from Sequence");
    this->sequence = new SequenceType<T>();
}

template<class T, template<class> class SequenceType>
MyDeque<T, SequenceType>::MyDeque(const T *arr, int size)
{
    static_assert(std::is_base_of<Sequence<T>, SequenceType<T>>(), "SequenceType is not derived from Sequence");
    this->sequence = new SequenceType<T>(arr, size);
}

template<class T, template<class> class SequenceType>
MyDeque<T, SequenceType>::MyDeque(const MyDeque<T, SequenceType> &deque)
{
    static_assert(std::is_base_of<Sequence<T>, SequenceType<T>>(), "SequenceType is not derived from Sequence");
    this->sequence = new SequenceType<T>(*(SequenceType<T> *)deque.sequence);
}

template<class T, template<class> class SequenceType>
MyDeque<T, SequenceType>::~MyDeque()
{
    delete sequence;
}

template<class T, template<class> class SequenceType>
int MyDeque<T, SequenceType>::GetSize() const
{
    return this->sequence->GetSize();
}

template<class T, template<class> class SequenceType>
bool MyDeque<T, SequenceType>::isEmpty() const
{
    return this->sequence->GetSize() == 0;
}

template<class T, template<class> class SequenceType>
void MyDeque<T, SequenceType>::PushBack(T item)
{
    this->sequence->Append(item);
}

template<class T, template<class> class SequenceType>
void MyDeque<T, SequenceType>::PushFront(T item)
{
    this->sequence->Prepend(item);
}

template<class T, template<class> class SequenceType>
void MyDeque<T, SequenceType>::PopBack()
{
    if(this->GetSize() == 0)
    {
        throw std::runtime_error("calling PopBack() in MyDeque with zero elements");
    }

    this->sequence->PopBack();
}

template<class T, template<class> class SequenceType>
void MyDeque<T, SequenceType>::PopFront()
{
    if(this->GetSize() == 0)
    {
        throw std::runtime_error("calling PopFront() in MyDeque with zero elements");
    }

    this->sequence->PopFront();
}

template<class T, template<class> class SequenceType>
MyDeque<T, SequenceType> MyDeque<T, SequenceType>::Concat(const MyDeque<T, SequenceType> &deque) const
{
    MyDeque<T, SequenceType> ret;
    delete ret.sequence;
    ret.sequence = this->sequence->Concat(deque.sequence);
    return ret;
}

template<class T, template<class> class SequenceType>
T MyDeque<T, SequenceType>::Back() const
{
    if (this->GetSize() == 0)
    {
        throw std::runtime_error("calling Back() in empty deque");
    }

    return this->sequence->GetLast();
}

template<class T, template<class> class SequenceType>
T MyDeque<T, SequenceType>::Front() const
{
    if (this->GetSize() == 0)
    {
        throw std::runtime_error("calling Front() in empty deque");
    }

    return this->sequence->GetFirst();
}

template<class T, template<class> class SequenceType>
void MyDeque<T, SequenceType>::Map(const std::function<void(T&)> &func)
{
    this->sequence->Map(func);
}

template<class T, template<class> class SequenceType>
void MyDeque<T, SequenceType>::Map(const std::function<void(T&)> &func, int startIndex, int endIndex)
{
    this->sequence->Map(func, startIndex, endIndex);
}

template<class T, template<class> class SequenceType>
T &MyDeque<T, SequenceType>::operator[](int index)
{
    return this->sequence->operator[](index);
}

template<class T, template<class> class SequenceType>
int MyDeque<T, SequenceType>::Find(const MyDeque<T, SequenceType> &deque, int startIndex) const
{
    return this->sequence->Find(deque.sequence, startIndex);
}

template<class T, template<class> class SequenceType>
MyDeque<T, SequenceType> MyDeque<T, SequenceType>::GetSubsequence(int startIndex, int endIndex) const
{
    MyDeque<T, SequenceType> ret;
    delete ret.sequence;
    ret.sequence = this->sequence->GetSubsequence(startIndex, endIndex);
    return ret;
}

template<class T, template<class> class SequenceType>
MyDeque<T, SequenceType> MyDeque<T, SequenceType>::Where(const std::function<bool(T)> &func) const
{
    MyDeque<T, SequenceType> newdeque;
    delete newdeque.sequence;
    newdeque.sequence = this->sequence->Where(func);
    return newdeque;
}

template<class T, template<class> class SequenceType>
T MyDeque<T, SequenceType>::Reduce(const std::function<T(T, T)> &func) const
{
    return this->sequence->Reduce(func);
}

template<class T, template<class> class SequenceType>
MyDeque<T, SequenceType> MyDeque<T, SequenceType>::operator=(const MyDeque<T, SequenceType> &deque)
{
    delete [] sequence;
    this->sequence = new SequenceType<T>(*deque.sequence);
    return (*this);
}


