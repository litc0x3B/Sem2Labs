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
    void peek(MyStack<T, SequenceType> & stack)
    {
        lab3UI::printStarString();
        lab3UI::output(stack.Peek());
    }
    
    template <class T, template <class> class SequenceType>
    void reduce(MyStack<T, SequenceType> & stack)
    {
        lab3UI::printStarString();
        std::cout << "Вывод максимального значения" << std::endl
             << "(для Person лексикографическое сравнение по имени)" << std::endl;

        auto start = lab3UI::getNow();
        T max = stack.Reduce([](T prev, T cur){return prev > cur ? prev : cur;});
        lab3UI::elapsedTimeOutput(start);
        
        lab3UI::printStarString();
        lab3UI::output(max);
    }

    template <class T, template <class> class SequenceType>
    void find(MyStack<T, SequenceType> & stack)
    {
        std::cout << "Введите подпоследовательность: " << std::endl;
        auto substack = input<T, SequenceType>();

        auto start = lab3UI::getNow();
        int result = stack.Find(substack);
        lab3UI::elapsedTimeOutput(start);

        lab3UI::printStarString();
        std::cout << "Индекс первого вхождения: " << result << std::endl;
    }

    template <class T, template <class> class SequenceType>
    void push(MyStack<T, SequenceType> & stack)
    {
        T item = lab3UI::input<T>();

        auto start = lab3UI::getNow();
        stack.Push(item);
        lab3UI::elapsedTimeOutput(start);
    }

    template <class T, template <class> class SequenceType>
    void pop(MyStack<T, SequenceType> & stack)
    {
        auto start = lab3UI::getNow();
        stack.Pop();
        lab3UI::elapsedTimeOutput(start);
    }

    template <class T, template <class> class SequenceType>
    void map(MyStack<T, SequenceType> & stack)
    {
        std::cout << "Увеличение каждого числа на 10" << std::endl;
        std::cout << "(для Person увеличение ID)" << std::endl;

        auto start = lab3UI::getNow();
        stack.Map([](T &item){item += 10;});
        lab3UI::elapsedTimeOutput(start);
    }

    template <class T, template <class> class SequenceType>
    void where(MyStack<T, SequenceType> & stack)
    {
        std::cout << "Составление стека, в котором все числа больше 10-ти" << std::endl;

        auto start = lab3UI::getNow();
        auto result = stack.Where([](T item){return item > 10;});
        lab3UI::elapsedTimeOutput(start);

        output(result);
    }

    template< template<class> class SequenceType>
    void wherePerson(MyStack<Person, SequenceType> &stack)
    {
        std::cout << "Вывод элементов с именами начинающимися на 'A' (английскую)" << std::endl;

        auto start = lab3UI::getNow();
        auto result = stack.Where([](Person item){return item.name.length() != 0 && item.name[0] == 'A';});
        lab3UI::elapsedTimeOutput(start);

        output(result);
    }

    template<> void where<Person, DynamicArraySequence>(MyStack<Person, DynamicArraySequence> & stack)
    {
        wherePerson(stack);
    }

    template<> void where<Person, LinkedListSequence>(MyStack<Person, LinkedListSequence> & stack)
    {
        wherePerson(stack);
    }

    template<class T, template<class> class SequenceType>
    void getSubsequence(MyStack<T, SequenceType> & stack)
    {
        std::cout << "Введите индекс первого элемента (начиная с нуля)" << std::endl;
        int startIndex;
        std::cin >> startIndex;

        std::cout << "Введите индекс последнего элемента (начиная с нуля)" << std::endl;
        int endIndex;
        std::cin >> endIndex;

        auto start = lab3UI::getNow();
        auto result = stack.GetSubsequence(startIndex, endIndex);
        lab3UI::elapsedTimeOutput(start);

        output(result);
    }

    template<class T, template<class> class SequenceType>
    void concat(MyStack<T, SequenceType> & stack)
    {
        auto inputStack = input<T, SequenceType>();

        auto start = lab3UI::getNow();
        auto result = stack.Concat(inputStack);
        lab3UI::elapsedTimeOutput(start);

        output(result);
    }

    template <class T, template <class> class SequenceType>
    void menu()
    {
        std::function<void(MyStack<T, SequenceType> &)> funcs[]
        {
            output<T, SequenceType>,
            getSize<T, SequenceType>,
            isEmpty<T, SequenceType>,
            peek<T, SequenceType>,
            reduce<T, SequenceType>,
            find<T, SequenceType>,
            push<T, SequenceType>,
            pop<T, SequenceType>,
            map<T, SequenceType>,
            where<T, SequenceType>,
            getSubsequence<T, SequenceType>,
            concat<T, SequenceType>
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