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

    static int CompFunc(const QueueItem &item1, const QueueItem &item2)
    {
        if (item1.priority > item2.priority) return 1;
        if (item1.priority < item2.priority) return -1;
        return 0;
    }

    BinTree<QueueItem> tree = BinTree<QueueItem>(CompFunc);

public:
    PriorityQueue(){}

    PriorityQueue(const PriorityQueue<T>& queue)
    {
        tree = queue.tree;
    }

    PriorityQueue<T> Map(const std::function<T(const T& value)> &handlerFunc) const 
    {
        PriorityQueue<T> newQueue;
        newQueue.tree.Map([handlerFunc](const QueueItem &item)
        {
            QueueItem newItem = {handlerFunc(item.value), item.priority};
            return newItem;
        });
        return newQueue;
    }

    PriorityQueue<T> Where(const std::function<bool(const T& value)> &handlerFunc) const
    {
        PriorityQueue<T> newQueue;
        newQueue.tree.Where([handlerFunc](const QueueItem &item)
        {
            QueueItem newItem = {handlerFunc(item.value), item.priority};
            return newItem;
        });
        return newQueue;
    }

    T Reduce(const std::function<T(const T&, const T&)> &handlerFunc, T identity) const   
    {
        return tree.Reduce([handlerFunc](const QueueItem &prevItem, const QueueItem &curItem)
        {
            QueueItem newItem = {handlerFunc(prevItem.value, curItem.value), 0};
            return newItem;
        }, {identity, 0});
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
    
    void Push(T item, int priority)  {tree.Add({item, priority});}

};