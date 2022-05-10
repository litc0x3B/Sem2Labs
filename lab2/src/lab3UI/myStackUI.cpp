#include "lab3UI/lab3UI.hpp"
#include "lab3UI/myStackUI.hpp"
#include "sequence/linkedListSequence.hpp"
#include "sequence/dynamicArraySequence.hpp"
#include "sequence/sequence.hpp"
#include "myStack.hpp"

namespace MyStackUI 
{   
    template <class T, template <class> class SequenceType>
    MyStack<T, SequenceType> input()
    {
        std::cout << "Введите размер стека: " << std::endl;
        int size;
        std::cin >> size;

        MyStack<T, SequenceType> stack;

        for (int i = 0; i < size; i++)
        {
            std::cout << "Введите значание " << i + 1 << ":" << std::endl;
            T item = lab3UI::input<T>();
            stack.Push(item);
        }

        return stack;
    }

    template <class T, template <class> class SequenceType>
    void output(MyStack<T, SequenceType> & stack)
    {
        lab3UI::printStarString();
        std::cout << "Вывод: " << std::endl;
        stack.Map([](T item){lab3UI::output(item);});
    }

    template <class T, template <class> class SequenceType>
    void getSize(MyStack<T, SequenceType> & stack)
    {
        lab3UI::printStarString();
        std::cout << "Вывод: " << stack.GetSize() << std::endl;
    }

    template <class T, template <class> class SequenceType>
    void isEmpty(MyStack<T, SequenceType> & stack)
    {
        lab3UI::printStarString();
        std::cout << (stack.isEmpty() ? "Стек пуст" : "Стек не пуст") << std::endl;
    }

    template <class T, template <class> class SequenceType>
    void Peek(MyStack<T, SequenceType> & stack)
    {
        lab3UI::printStarString();
        std::cout << "Вывод: " << stack.Peek() << std::endl;
    }
    
    template <template <class> class SequenceType>
    void Reduce(MyStack<float, SequenceType> & stack)
    {
        lab3UI::printStarString();
        std::cout << 
    }

    template <class T, template <class> class SequenceType>
    void menu()
    {
        
        std::function<void(MyStack<T, SequenceType> &)> funcs[]
        {
            output<T, SequenceType>
        };

        int funcsSize = sizeof(funcs) / sizeof(std::function<void(MyStack<T, SequenceType> &)>);

        MyStack<T, SequenceType> stack = input<T, SequenceType>();

        while (true)
        {
            lab3UI::printStarString();
            std::cout << "Выберете команду: " << std::endl;
            std::cout << "1)\tВывод" << std::endl;
            std::cout << "2)\tGetSize" << std::endl;
            std::cout << "3)\tisEmpty" << std::endl;
            std::cout << "4)\tPeek" << std::endl;
            std::cout << "5)\tReduce" << std::endl;
            std::cout << "6)\tFind" << std::endl;
            std::cout << "7)\tPush" << std::endl;
            std::cout << "8)\tPop" << std::endl;
            std::cout << "9)\tMap" << std::endl;
            std::cout << "10)\tWhere" << std::endl;
            std::cout << "11)\tGetSubsequence" << std::endl;
            std::cout << "12)\tConcat" << std::endl;
            std::cout << "13)\t" << (lab3UI::autoInput ? "Выключить автоввод" : "Включить автоввод") << std::endl;
            std::cout << "14)\tВыход" << std::endl;
    
            int cmd;
            std::cin >> cmd;
    
            if (cmd >= 1 && cmd <= funcsSize)
            {
                funcs[cmd - 1](stack);
            }
            else if(cmd == 13)
            {
                lab3UI::autoInput = !lab3UI::autoInput;
            }
            else if(cmd == 14)
            {
                return;
            }
            else 
            {   lab3UI::printStarString();
                std::cout << "Неизвестная команда" << std::endl;
            }
        }
    }

    void initMenu(lab3UI::ContainerInfo containerInfo)
    {
        if (containerInfo.sequenceType == lab3UI::SequenceType::array)
        {
            if (containerInfo.dataType == lab3UI::DataType::floatType)
            {
                menu<float, DynamicArraySequence>();
            }
            else if (containerInfo.dataType == lab3UI::DataType::personType)
            {
                menu<Person, DynamicArraySequence>();
            }
        }

        else if (containerInfo.sequenceType == lab3UI::SequenceType::list)
        {
            if (containerInfo.dataType == lab3UI::DataType::floatType)
            {
                menu<float, LinkedListSequence>();
            }
            else if (containerInfo.dataType == lab3UI::DataType::personType)
            {
                menu<Person, LinkedListSequence>();
            }
        }
    }
}