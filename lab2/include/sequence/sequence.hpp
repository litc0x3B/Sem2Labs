#pragma once

enum SequenceType
    {
        undefined,
        list,
        array,
    };

template<typename T>
class Sequence
{
protected:
    SequenceType sequenceType = undefined;
public:
    virtual ~Sequence() {};

    SequenceType GetType() {return sequenceType;}

    virtual T &GetFirst() = 0;
    virtual T &GetLast() = 0;
    virtual int GetActualSize() const = 0;
    virtual int GetSize() const = 0;

    virtual T &operator[](int index) const = 0;

    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void PopBack() = 0;
    virtual void PopFront() = 0;
    virtual void Delete(int index) = 0;
    virtual void InsertAt(T item, int index) = 0;

    virtual Sequence<T> *Concat(Sequence <T> *list) const = 0;
    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) const = 0;
};
