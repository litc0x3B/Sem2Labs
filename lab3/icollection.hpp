#pragma once
#include <functional>

template<class T> class ICollection
{
public:
    virtual int GetSize() const = 0;
    virtual void Add(T item) = 0;
    virtual void Remove(T item) = 0;
    virtual bool Search(T item) const = 0;
    virtual bool Search(T item, T &foundItem) const = 0;

    virtual T Reduce(const std::function<T(const T&, const T&)> &handlerFunc, T identity) const = 0;
    virtual ICollection<T> *MapC(const std::function<T(const T& item)> &handlerFunc) const = 0;
    virtual ICollection<T> *WhereC(const std::function<bool(const T& item)> &handlerFunc) const = 0;
};