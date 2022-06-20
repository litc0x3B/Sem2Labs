#pragma once

#include "binTree.hpp"
#include "icollection.hpp"

template<class T> class PriorityQueue
{
private:
    struct QueueItem
    {
        T value;
        int priority;
    };

    BinTree<QueueItem> tree;

    static int compFunc(const QueueItem &item1, const QueueItem &item2)
    {
        if (item1.priority > item2.priority) return 1;
        if (item1.priority < item2.priority) return -1;
        else return 0;
    }

public:
    PriorityQueue()
    {
        tree = tree(compFunc);
    }

    PriorityQueue<T> Map(const std::function<T(const T& value)> &handlerFunc) const 
    {
        PriorityQueue<T> newQueue;
        newQueue.tree.Map([handlerFunc](const QueueItem &item){return handlerFunc(item.value);});
        return newQueue;
    }

    PriorityQueue<T> Where(const std::function<bool(const T& value)> &handlerFunc) const
    {
        PriorityQueue<T> newQueue;
        newQueue.tree.Where([handlerFunc](const QueueItem &item){return handlerFunc(item.value);});
        return newQueue;
    }

    T Reduce(const std::function<T(const T&, const T&)> &handlerFunc, T identity) const override 
    {
        return tree.Reduce([handlerFunc](const QueueItem &prevItem, const QueueItem &curItem)
        {
            return handlerFunc(prevItem.value, curItem.value);
        }, identity);
    }

    T Pop()
    {
        QueueItem item = tree.GetMin();
        tree.Remove(item);
        return item.value;
    }

    T Peek()
    {
        QueueItem item = tree.GetMin();
        return item.value;
    }
    
    void Add(T item, int priority) override {tree.Add({item, priority});}

};