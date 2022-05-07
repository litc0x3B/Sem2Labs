#pragma once
#include <functional>
#include "sequence/sequence.hpp"
#include "sequence/linkedListSequence.hpp"

template<class T, template<class> class SequenceType = LinkedListSequence>
class MyStack
{
private:
    Sequence<T> *sequence;
public:
    MyStack();
    MyStack(const MyStack<T, SequenceType> &stack);
    MyStack(const T *arr, int size);

    ~MyStack();

    int GetSize() const;
    bool isEmpty() const;
    T Peek() const;
    T Reduce(const std::function<T(T prev, T current)> &func) const;
    int Find(MyStack<T, SequenceType> *stack, int startIndex = 0) const;

    void Push(T item);
    void Pop();
    void Map(const std::function<void(T&)> &func);
    void Map(const std::function<void(T&)> &func, int startIndex, int endIndex);

    T &operator[](int index);

    MyStack<T, SequenceType> *Where(const std::function<bool(T)> &func) const;
    MyStack<T, SequenceType> *GetSubsequence(int startIndex, int endIndex) const;
    MyStack<T, SequenceType> *Concat(const MyStack<T, SequenceType> *stack) const;
};

template<class T, template<class> class SequenceType>
MyStack<T, SequenceType>::MyStack()
{
    static_assert(std::is_base_of<Sequence<T>, SequenceType<T>>(), "SequenceType is not derived from Sequence");
    this->sequence = new SequenceType<T>();
}

template<class T, template<class> class SequenceType>
MyStack<T, SequenceType>::MyStack(const T *arr, int size)
{
    static_assert(std::is_base_of<Sequence<T>, SequenceType<T>>(), "SequenceType is not derived from Sequence");
    this->sequence = new SequenceType<T>(arr, size);
}

template<class T, template<class> class SequenceType>
MyStack<T, SequenceType>::MyStack(const MyStack<T, SequenceType> &stack)
{
    static_assert(std::is_base_of<Sequence<T>, SequenceType<T>>(), "SequenceType is not derived from Sequence");
    this->sequence = new SequenceType<T>(*(SequenceType<T> *)stack.sequence);
}

template<class T, template<class> class SequenceType>
MyStack<T, SequenceType>::~MyStack()
{
    delete sequence;
}

template<class T, template<class> class SequenceType>
int MyStack<T, SequenceType>::GetSize() const
{
    return this->sequence->GetSize();
}

template<class T, template<class> class SequenceType>
bool MyStack<T, SequenceType>::isEmpty() const
{
    return this->sequence->GetSize() == 0;
}

template<class T, template<class> class SequenceType>
void MyStack<T, SequenceType>::Push(T item)
{
    return this->sequence->Append(item);
}

template<class T, template<class> class SequenceType>
void MyStack<T, SequenceType>::Pop()
{
    if(this->GetSize() == 0)
    {
        throw std::runtime_error("calling Pop in MyStack with zero elements");
    }

    return this->sequence->PopBack();
}

template<class T, template<class> class SequenceType>
MyStack<T, SequenceType> *MyStack<T, SequenceType>::Concat(const MyStack<T, SequenceType> *stack) const
{
    auto *ret = new MyStack<T, SequenceType>;
    delete ret->sequence;
    ret->sequence = this->sequence->Concat(stack->sequence);
    return ret;
}

template<class T, template<class> class SequenceType>
T MyStack<T, SequenceType>::Peek() const
{
    if (this->GetSize() == 0)
    {
        throw std::runtime_error("calling Peek() in empty stack");
    }

    return this->sequence->GetLast();
}
template<class T, template<class> class SequenceType>
void MyStack<T, SequenceType>::Map(const std::function<void(T&)> &func)
{
    this->sequence->Map(func);
}

template<class T, template<class> class SequenceType>
void MyStack<T, SequenceType>::Map(const std::function<void(T&)> &func, int startIndex, int endIndex)
{
    this->sequence->Map(func, startIndex, endIndex);
}

template<class T, template<class> class SequenceType>
T &MyStack<T, SequenceType>::operator[](int index)
{
    return this->sequence->operator[](index);
}

template<class T, template<class> class SequenceType>
int MyStack<T, SequenceType>::Find(MyStack<T, SequenceType> *stack, int startIndex) const
{
    return this->sequence->Find(stack->sequence, startIndex);
}

template<class T, template<class> class SequenceType>
MyStack<T, SequenceType> *MyStack<T, SequenceType>::GetSubsequence(int startIndex, int endIndex) const
{
    auto *ret = new MyStack<T, SequenceType>();
    delete ret->sequence;
    ret->sequence = this->sequence->GetSubsequence(startIndex, endIndex);
    return ret;
}

template<class T, template<class> class SequenceType>
MyStack<T, SequenceType> *MyStack<T, SequenceType>::Where(const std::function<bool(T)> &func) const
{
    auto *newStack = new MyStack<T, SequenceType>();
    delete newStack->sequence;
    newStack->sequence = this->sequence->Where(func);
    return newStack;
}

template<class T, template<class> class SequenceType>
T MyStack<T, SequenceType>::Reduce(const std::function<T(T, T)> &func) const
{
    return this->sequence->Reduce(func);
}


