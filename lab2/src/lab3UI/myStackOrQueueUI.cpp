#include "lab3UI/lab3UI.hpp"
#include "lab3UI/myStackOrQueueUI.hpp"
#include "sequence/linkedListSequence.hpp"
#include "sequence/dynamicArraySequence.hpp"
#include "sequence/sequence.hpp"
#include "myStack.hpp"
#include "myQueue.hpp"

namespace myStackOrQueueUI 
{   
    template <class T, template <class> class SequenceType, template <class, template <class> class> class ContainerType>
    ContainerType<T, SequenceType> input()
    {
        std::cout << "Введите размер: " << std::endl;
        int size;
        std::cin >> size;

        ContainerType<T, SequenceType> container;

        for (int i = 0; i < size; i++)
        {
            std::cout << "Введите значание " << i + 1 << ":" << std::endl;
            T item = lab3UI::input<T>();
            container.Push(item);
        }

        return container;
    }

    template <class T, template <class> class SequenceType, template <class, template <class> class> class ContainerType>
    void output(ContainerType<T, SequenceType> & container)
    {
        lab3UI::printStarString();
        std::cout << "Вывод: " << std::endl;
        container.Map([](T item){lab3UI::output(item);});
    }

    template <class T, template <class> class SequenceType, template <class, template <class> class> class ContainerType>
    void getSize(ContainerType<T, SequenceType> & container)
    {
        lab3UI::printStarString();
        std::cout << "Вывод: " << container.GetSize() << std::endl;
    }

    template <class T, template <class> class SequenceType, template <class, template <class> class> class ContainerType>
    void isEmpty(ContainerType<T, SequenceType> & container)
    {
        lab3UI::printStarString();
        std::cout << (container.isEmpty() ? "Контейнер пуст" : "Контейнер не пуст") << std::endl;
    }

    template <class T, template <class> class SequenceType, template <class, template <class> class> class ContainerType>
    void peek(ContainerType<T, SequenceType> & container)
    {
        lab3UI::printStarString();
        lab3UI::output(container.Peek());
    }
    
    template <class T, template <class> class SequenceType, template <class, template <class> class> class ContainerType>
    void reduce(ContainerType<T, SequenceType> & container)
    {
        lab3UI::printStarString();
        std::cout << "Вывод максимального значения" << std::endl
             << "(для Person лексикографическое сравнение по имени)" << std::endl;

        auto start = lab3UI::getNow();
        T max = container.Reduce([](T prev, T cur){return prev > cur ? prev : cur;});
        lab3UI::elapsedTimeOutput(start);
        
        lab3UI::printStarString();
        lab3UI::output(max);
    }

    template <class T, template <class> class SequenceType, template <class, template <class> class> class ContainerType>
    void find(ContainerType<T, SequenceType> & container)
    {
        std::cout << "Введите подпоследовательность: " << std::endl;
        auto subcontainer = input<T, SequenceType,ContainerType>();

        auto start = lab3UI::getNow();
        int result = container.Find(subcontainer);
        lab3UI::elapsedTimeOutput(start);

        lab3UI::printStarString();
        std::cout << "Индекс первого вхождения: " << result << std::endl;
    }

    template <class T, template <class> class SequenceType, template <class, template <class> class> class ContainerType>
    void push(ContainerType<T, SequenceType> & container)
    {
        T item = lab3UI::input<T>();

        auto start = lab3UI::getNow();
        container.Push(item);
        lab3UI::elapsedTimeOutput(start);
    }

    template <class T, template <class> class SequenceType, template <class, template <class> class> class ContainerType>
    void pop(ContainerType<T, SequenceType> & container)
    {
        auto start = lab3UI::getNow();
        container.Pop();
        lab3UI::elapsedTimeOutput(start);
    }

    template <class T, template <class> class SequenceType, template <class, template <class> class> class ContainerType>
    void map(ContainerType<T, SequenceType> & container)
    {
        std::cout << "Увеличение каждого числа на 10" << std::endl;
        std::cout << "(для Person увеличение ID)" << std::endl;

        auto start = lab3UI::getNow();
        container.Map([](T &item){item += 10;});
        lab3UI::elapsedTimeOutput(start);
    }

    template <class T, template <class> class SequenceType, template <class, template <class> class> class ContainerType>
    void where(ContainerType<T, SequenceType> & container)
    {
        std::cout << "Получение контейнера, в котором все числа больше 10-ти" << std::endl;

        auto start = lab3UI::getNow();
        auto result = container.Where([](T item){return item > 10;});
        lab3UI::elapsedTimeOutput(start);

        output(result);
    }

    template< template<class> class SequenceType, template <class, template <class> class> class ContainerType>
    void wherePerson(ContainerType<Person, SequenceType> &container)
    {
        std::cout << "Вывод элементов с именами начинающимися на 'A' (английскую)" << std::endl;

        auto start = lab3UI::getNow();
        auto result = container.Where([](Person item){return item.name.length() != 0 && item.name[0] == 'A';});
        lab3UI::elapsedTimeOutput(start);

        output(result);
    }

    template<> void where<Person, DynamicArraySequence, MyStack>(MyStack<Person, DynamicArraySequence> & container)
    {
        wherePerson(container);
    }

    template<> void where<Person, LinkedListSequence, MyStack>(MyStack<Person, LinkedListSequence> & container)
    {
        wherePerson(container);
    }

    template<> void where<Person, DynamicArraySequence, MyQueue>(MyQueue<Person, DynamicArraySequence> & container)
    {
        wherePerson(container);
    }

    template<> void where<Person, LinkedListSequence, MyQueue>(MyQueue<Person, LinkedListSequence> & container)
    {
        wherePerson(container);
    }

    template<class T, template<class> class SequenceType, template <class, template <class> class> class ContainerType>
    void getSubsequence(ContainerType<T, SequenceType> & container)
    {
        std::cout << "Введите индекс первого элемента (начиная с нуля)" << std::endl;
        int startIndex;
        std::cin >> startIndex;

        std::cout << "Введите индекс последнего элемента (начиная с нуля)" << std::endl;
        int endIndex;
        std::cin >> endIndex;

        auto start = lab3UI::getNow();
        auto result = container.GetSubsequence(startIndex, endIndex);
        lab3UI::elapsedTimeOutput(start);

        output(result);
    }

    template<class T, template<class> class SequenceType, template <class, template <class> class> class ContainerType>
    void concat(ContainerType<T, SequenceType> & container)
    {
        auto inputContainer = input<T, SequenceType, ContainerType>();

        auto start = lab3UI::getNow();
        auto result = container.Concat(inputContainer);
        lab3UI::elapsedTimeOutput(start);

        output(result);
    }

    template <class T, template <class> class SequenceType, template <class, template <class> class> class ContainerType>
    void menu()
    {
        std::function<void(ContainerType<T, SequenceType> &)> funcs[]
        {
            output<T, SequenceType, ContainerType>,
            getSize<T, SequenceType, ContainerType>,
            isEmpty<T, SequenceType, ContainerType>,
            peek<T, SequenceType, ContainerType>,
            reduce<T, SequenceType, ContainerType>,
            find<T, SequenceType, ContainerType>,
            push<T, SequenceType, ContainerType>,
            pop<T, SequenceType, ContainerType>,
            map<T, SequenceType, ContainerType>,
            where<T, SequenceType, ContainerType>,
            getSubsequence<T, SequenceType, ContainerType>,
            concat<T, SequenceType, ContainerType>,
        };

        int funcsSize = sizeof(funcs) / sizeof(std::function<void(ContainerType<T, SequenceType> &)>);

        ContainerType<T, SequenceType> container = input<T, SequenceType, ContainerType>();

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
                funcs[cmd - 1](container);
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
        if (containerInfo.containerType == lab3UI::ContainerType::stack)
        {
            if (containerInfo.sequenceType == lab3UI::SequenceType::array)
            {
                if (containerInfo.dataType == lab3UI::DataType::floatType)
                {
                    menu<float, DynamicArraySequence, MyStack>();
                }
                else if (containerInfo.dataType == lab3UI::DataType::personType)
                {
                    menu<Person, DynamicArraySequence, MyStack>();
                }
            }

            else if (containerInfo.sequenceType == lab3UI::SequenceType::list)
            {
                if (containerInfo.dataType == lab3UI::DataType::floatType)
                {
                    menu<float, LinkedListSequence, MyStack>();
                }
                else if (containerInfo.dataType == lab3UI::DataType::personType)
                {
                    menu<Person, LinkedListSequence, MyStack>();
                }
            }
        }

        else if (containerInfo.containerType == lab3UI::ContainerType::queue)
        {
            if (containerInfo.sequenceType == lab3UI::SequenceType::array)
            {
                if (containerInfo.dataType == lab3UI::DataType::floatType)
                {
                    menu<float, DynamicArraySequence, MyQueue>();
                }
                else if (containerInfo.dataType == lab3UI::DataType::personType)
                {
                    menu<Person, DynamicArraySequence, MyQueue>();
                }
            }

            else if (containerInfo.sequenceType == lab3UI::SequenceType::list)
            {
                if (containerInfo.dataType == lab3UI::DataType::floatType)
                {
                    menu<float, LinkedListSequence, MyQueue>();
                }
                else if (containerInfo.dataType == lab3UI::DataType::personType)
                {
                    menu<Person, LinkedListSequence, MyQueue>();
                }
            }
        }
    }
}