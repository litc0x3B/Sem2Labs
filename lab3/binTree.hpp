#pragma once
#include <functional>
#include <stdexcept>
#include <string>



template <class T> struct BinTreeNode 
{
    BinTreeNode(T value)
    {
        this->value = value;
    }

    BinTreeNode *rightNode = nullptr;
    BinTreeNode *leftNode = nullptr;
    T value;
};

template <class T, class WrappedFuncArg> class HandlerFuncWrapper
{
protected:
    std::function<void(WrappedFuncArg)> handlerFunc;

public:
    HandlerFuncWrapper(const std::function <void(WrappedFuncArg)> &handlerFunc)
    {
        this->handlerFunc = handlerFunc;
    }

    virtual void Call(BinTreeNode<T>**) = 0;
};

template <class T> class HandlerNodeArg : public HandlerFuncWrapper<T, BinTreeNode<T>**>
{
public:
    HandlerNodeArg(const std::function <void(BinTreeNode<T>**)> &handlerFunc) : HandlerFuncWrapper<T, BinTreeNode<T>**>(handlerFunc) {}

    void Call(BinTreeNode<T>** node) override
    {
        this->handlerFunc(node);
    }
};

template <class T> class HandlerValueArg : public HandlerFuncWrapper<T, T&>
{
public:
    HandlerValueArg(const std::function <void(T&)> &handlerFunc) : HandlerFuncWrapper<T, T&>(handlerFunc) {}

    void Call(BinTreeNode<T>** node) override
    {
        this->handlerFunc((*node)->value);
    }
};


template <class T> class BinTree 
{
private:
    BinTreeNode<T> *root = nullptr;
    std::function<int(const T&, const T&)> comparer;
    int size = 0;

    static int Comp(const T &a, const T &b)
    {  
        if (a > b) return 1;
        if (a < b) return -1;
        return 0;
    }

    static void CheckTraverseOptions(std::string orderOptions)
    {
        if
        (
            orderOptions.size() != 3 || 
            orderOptions.find("L") == std::string::npos || 
            orderOptions.find("R") == std::string::npos || 
            orderOptions.find("N") == std::string::npos
        )
        {
            throw std::invalid_argument("Invalid order options");
        }
    }

    void _Insert(BinTreeNode<T> *curNode, BinTreeNode<T> *newNode) 
    {
        int comp = comparer(newNode->value, curNode->value);
        BinTreeNode<T> **nextNode;

        if (comp > 0) 
        {
            nextNode = &(curNode->rightNode);
        }
        else if (comp < 0) 
        {
            nextNode = &(curNode->leftNode);
        }
        else 
        {
            return;
        }

        if (*nextNode == nullptr)
        {
            size++;
            (*nextNode) = newNode;
            return;
        }

        _Insert(*nextNode, newNode);
    }

    template<class WrappedFuncArg> 
    void _Traverse(HandlerFuncWrapper<T, WrappedFuncArg> *wrapper, std::string orderOptions, BinTreeNode<T> **nextNode)
    {

        if (*nextNode == nullptr)
        {
            return;
        }

        BinTreeNode<T> *node = *nextNode;
        for (int i = 0; i < 3; i++)
        {
            char nextAction = orderOptions[i];
            switch (nextAction) 
            {
                case 'L': _Traverse(wrapper, orderOptions, &node->leftNode); break;
                case 'R': _Traverse(wrapper, orderOptions, &node->rightNode); break;
                case 'N': wrapper->Call(nextNode); break;
                default: throw std::invalid_argument("Invalid order options passed to _Traverse function (it's not your fault)"); break;
            }
        }
    }


    void _TraverseNodes(const std::function <void(BinTreeNode<T>**)> handlerFunc, BinTreeNode<T> *root, std::string orderOptions = "LNR")
    {
        CheckTraverseOptions(orderOptions);
        HandlerNodeArg<T> wrapper(handlerFunc);
        _Traverse<BinTreeNode<T>**>(&wrapper, orderOptions, &root);
    }

    void _TraverseNodes(const std::function <void(BinTreeNode<T>**)> &handlerFunc, std::string orderOptions = "LNR")
    {
        _TraverseNodes(handlerFunc, root, orderOptions);
    }

    void _Clear()
    {
        _TraverseNodes([](BinTreeNode<T> **node)
        {
            delete *node;
        }, "LRN");

        root = nullptr;
        size = 0;
    }

    void _InsertFromTree(BinTree<T> &tree)
    {
        tree.Traverse([&](const T &value)
        {
            this->Insert(value);
        }, "NLR");
    }

    void _Copy(BinTree<T> &tree)
    {
        if (this == &tree)
        {
            return;
        }

        this->comparer = tree.comparer;
        this->_Clear();
        this->_InsertFromTree(tree);

        return;
    }

    bool _Search(const T &item, BinTreeNode<T> *curNode, T &foundItem)
    {
        if (curNode == nullptr)
        {
            return false;
        }

        int comp = comparer(item, curNode->value);

        if (comp > 0)
        {
            return _Search(item, curNode->rightNode, foundItem);
        }
        else if (comp < 0)
        {
            return _Search(item, curNode->leftNode, foundItem);
        }
        else 
        {
            foundItem = curNode->value;
            return true;
        }
    }

public:
    explicit BinTree(const std::function <int(const T&, const T&)> &comparer)
    {
        this->comparer = comparer;
    }

    BinTree(BinTree<T> &&tree)
    {
        _Copy(tree);
    }

    BinTree(BinTree<T> &tree)
    {
        _Copy(tree);
    }

    BinTree<T> &operator=(BinTree<T> &&tree)
    {
        _Copy(tree);
        return *this;
    }

    BinTree<T> &operator=(BinTree<T> &tree)
    {
        _Copy(tree);
        return *this;
    }

    BinTree()
    {
        this->comparer = this->Comp;
    }


    ~BinTree()
    {
        _Clear();
    }

    int GetSize() 
    {
        return size;
    }

    bool Search(T item)
    {
        T placeholder;
        return _Search(item, root, placeholder);
    }

    bool Search(T item, T &foundItem)
    {
        return _Search(item, root, foundItem);
    }
    
    void Traverse(const std::function <void(T&)> &handlerFunc, std::string orderOptions = "LNR")
    {
        CheckTraverseOptions(orderOptions);
        HandlerValueArg<T> wrapper(handlerFunc);
        _Traverse<T&>(&wrapper, orderOptions, &root);
    }

    BinTree<T> Where(const std::function<bool(const T&)> &handlerFunc)
    {
        BinTree<T> newTree;
        Traverse([&newTree, handlerFunc](T &value)
        {
            if (handlerFunc(value))
            {
                newTree.Insert(value);
            }
        }, "NLR");

        return newTree;
    }

    BinTree<T> Map(const std::function <T(const T&)> &handlerFunc)
    {
        BinTree<T> newTree(comparer);


        Traverse([handlerFunc, &newTree](T &value) 
        {
            T newValue = handlerFunc(value);
            newTree.Insert(newValue);
        }, "NLR");
        return newTree;
    }

    void Insert(T item) 
    {
        BinTreeNode<T> *newNode = new BinTreeNode<T>(item);

        if (root == nullptr) 
        {
            size++;
            root = newNode;
            return;
        }

        _Insert(root, newNode);
    }
};