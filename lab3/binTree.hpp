#pragma once
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <string>
#include <random>
#include <iostream>


template <class T> struct BinTreeNode 
{

    BinTreeNode *rightNode = nullptr;
    BinTreeNode *leftNode = nullptr;
    int size = 1;
    T value;


    BinTreeNode(const T &value)
    {

        this->value = value;
    }

    //delete later
    static int level; 
    void print()
    {
        for (int ix = 0; ix < level; ++ix) std::cout << ' ';
        std::cout << value << std::endl;
        ++level;
        if (leftNode)
        {
            leftNode->print();
            --level;
        }
        if (rightNode)
        {
            rightNode->print();
            --level;
        }
    }
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


    static int _Comp(const T &a, const T &b)
    {  
        if (a > b) return 1;
        if (a < b) return -1;
        return 0;
    }

    static void _CheckTraverseOptions(std::string orderOptions)
    {
        if
        (
            orderOptions.size() != 3 || 
            orderOptions.find("L") == std::string::npos || 
            orderOptions.find("R") == std::string::npos || 
            orderOptions.find("N") == std::string::npos
        )
        {
            throw std::invalid_argument("Invalid traverse order options");
        }
    }

    static int _GetSize(BinTreeNode<T> *node)
    {
        if (node != nullptr)
        {
            return node->size;
        }
        else 
        {
            return 0;
        }
    }

    static void _FixSize(BinTreeNode<T> *node)
    {
        node->size = _GetSize(node->leftNode) + _GetSize(node->rightNode) + 1;
    }


    static BinTreeNode<T> *_RotateRight(BinTreeNode<T> *rightNode)
    {
        BinTreeNode<T> *leftNode = rightNode->leftNode;

        if (leftNode == nullptr)
        {
            return rightNode;
        }

        rightNode->leftNode = leftNode->rightNode;
        leftNode->rightNode = rightNode;

        leftNode->size = rightNode->size;
        _FixSize(rightNode);

        return leftNode;
    }

    static BinTreeNode<T> *_RotateLeft(BinTreeNode<T> *leftNode)
    {
        BinTreeNode<T> *rightNode = leftNode->rightNode;

        if (rightNode == nullptr)
        {
            return leftNode;
        }

        leftNode->rightNode = rightNode->leftNode;
        rightNode->leftNode = leftNode;

        rightNode->size = leftNode->size;
        _FixSize(leftNode);

        return rightNode;
    }

    BinTreeNode<T> *_InsertRoot(BinTreeNode<T> *node, const T &value)
    {
        if (node == nullptr)
        {
            return new BinTreeNode<T>(value);
        }

        int comp = comparer(value, node->value);

        if (comp > 0)
        {
            node->rightNode = _InsertRoot(node->rightNode, value);
            return _RotateLeft(node);
        }
        else if (comp < 0)
        {
            node->leftNode = _InsertRoot(node->leftNode, value);
            return _RotateRight(node);
        }
        else
        {
            return node;
        }

    }

    BinTreeNode<T> *_Insert(BinTreeNode<T> *node, const T &value) 
    {
        if (node == nullptr)
        {
            return new BinTreeNode<T>(value);
        }

        int randNum = std::rand();
        if (randNum % (_GetSize(node) + 1) == 0)
        {
            return _InsertRoot(node, value);
        }

        int comp = comparer(value, node->value);

        if (comp > 0)
        {
            node->rightNode = _Insert(node->rightNode, value);
        }
        else if (comp < 0)
        {
            node->leftNode = _Insert(node->leftNode, value);
        }

        _FixSize(node);
        return node;
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
        _CheckTraverseOptions(orderOptions);
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
        std::srand(time(NULL));
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
        this->comparer = this->_Comp;
        std::srand(time(NULL));
    }


    ~BinTree()
    {
        _Clear();
    }

    int GetSize() 
    {
        return root->size;
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
        _CheckTraverseOptions(orderOptions);
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
        root = _Insert(root, item);
    }
};