#pragma once
#include <functional>
#include "sequence/sequence.hpp"
#include "sequence/linkedListSequence.hpp"

template<class T, template<class> class SequenceType = LinkedListSequence>
class MyQueue
{
private:
    Sequence<T> *sequence;
public:
    MyQueue();
    MyQueue(const MyQueue<T, SequenceType> &queue);
    MyQueue(const T *arr, int size);

    ~MyQueue();

    int GetSize() const;
    bool isEmpty() const;
    T Peek() const;
    T Reduce(const std::function<T(T prev, T current)> &func) const;
    int Find(const MyQueue<T, SequenceType> &queue, int startIndex = 0) const;

    void Push(T item);
    void Pop();
    void Map(const std::function<void(T&)> &func);
    void Map(const std::function<void(T&)> &func, int startIndex, int endIndex);

    MyQueue<T, SequenceType> operator=(const MyQueue<T, SequenceType> &queue);
    T &operator[](int index);

    MyQueue<T, SequenceType> Where(const std::function<bool(T)> &func) const;
    MyQueue<T, SequenceType> GetSubsequence(int startIndex, int endIndex) const;
    MyQueue<T, SequenceType> Concat(const MyQueue<T, SequenceType> &queue) const;
};

template<class T, template<class> class SequenceType>
MyQueue<T, SequenceType>::MyQueue()
{
    static_assert(std::is_base_of<Sequence<T>, SequenceType<T>>(), "SequenceType is not derived from Sequence");
    this->sequence = new SequenceType<T>();
}

template<class T, template<class> class SequenceType>
MyQueue<T, SequenceType>::MyQueue(const T *arr, int size)
{
    static_assert(std::is_base_of<Sequence<T>, SequenceType<T>>(), "SequenceType is not derived from Sequence");
    this->sequence = new SequenceType<T>(arr, size);
}

template<class T, template<class> class SequenceType>
MyQueue<T, SequenceType>::MyQueue(const MyQueue<T, SequenceType> &queue)
{
    static_assert(std::is_base_of<Sequence<T>, SequenceType<T>>(), "SequenceType is not derived from Sequence");
    this->sequence = new SequenceType<T>(*(SequenceType<T> *)queue.sequence);
}

template<class T, template<class> class SequenceType>
MyQueue<T, SequenceType>::~MyQueue()
{
    delete sequence;
}

template<class T, template<class> class SequenceType>
int MyQueue<T, SequenceType>::GetSize() const
{
    return this->sequence->GetSize();
}

template<class T, template<class> class SequenceType>
bool MyQueue<T, SequenceType>::isEmpty() const
{
    return this->sequence->GetSize() == 0;
}

template<class T, template<class> class SequenceType>
void MyQueue<T, SequenceType>::Push(T item)
{
    return this->sequence->Append(item);
}

template<class T, template<class> class SequenceType>
void MyQueue<T, SequenceType>::Pop()
{
    if(this->GetSize() == 0)
    {
        throw std::runtime_error("calling Pop in MyQueue with zero elements");
    }

    return this->sequence->PopFront();
}

template<class T, template<class> class SequenceType>
MyQueue<T, SequenceType> MyQueue<T, SequenceType>::Concat(const MyQueue<T, SequenceType> &queue) const
{
    MyQueue<T, SequenceType> ret;
    delete ret.sequence;
    ret.sequence = this->sequence->Concat(queue.sequence);
    return ret;
}

template<class T, template<class> class SequenceType>
T MyQueue<T, SequenceType>::Peek() const
{
    if (this->GetSize() == 0)
    {
        throw std::runtime_error("calling Peek() in empty queue");
    }

    return this->sequence->GetFirst();
}
template<class T, template<class> class SequenceType>
void MyQueue<T, SequenceType>::Map(const std::function<void(T&)> &func)
{
    this->sequence->Map(func);
}

template<class T, template<class> class SequenceType>
void MyQueue<T, SequenceType>::Map(const std::function<void(T&)> &func, int startIndex, int endIndex)
{
    this->sequence->Map(func, startIndex, endIndex);
}

template<class T, template<class> class SequenceType>
T &MyQueue<T, SequenceType>::operator[](int index)
{
    return this->sequence->operator[](index);
}

template<class T, template<class> class SequenceType>
int MyQueue<T, SequenceType>::Find(const MyQueue<T, SequenceType> &queue, int startIndex) const
{
    return this->sequence->Find(queue.sequence, startIndex);
}

template<class T, template<class> class SequenceType>
MyQueue<T, SequenceType> MyQueue<T, SequenceType>::GetSubsequence(int startIndex, int endIndex) const
{
    MyQueue<T, SequenceType> ret;
    delete ret.sequence;
    ret.sequence = this->sequence->GetSubsequence(startIndex, endIndex);
    return ret;
}

template<class T, template<class> class SequenceType>
MyQueue<T, SequenceType> MyQueue<T, SequenceType>::Where(const std::function<bool(T)> &func) const
{
    MyQueue<T, SequenceType> newQueue;
    delete newQueue.sequence;
    newQueue.sequence = this->sequence->Where(func);
    return newQueue;
}

template<class T, template<class> class SequenceType>
T MyQueue<T, SequenceType>::Reduce(const std::function<T(T, T)> &func) const
{
    return this->sequence->Reduce(func);
}

template<class T, template<class> class SequenceType>
MyQueue<T, SequenceType> MyQueue<T, SequenceType>::operator=(const MyQueue<T, SequenceType> &queue)
{
    delete [] sequence;
    this->sequence = new SequenceType<T>(*queue.sequence);
    return (*this);
}


