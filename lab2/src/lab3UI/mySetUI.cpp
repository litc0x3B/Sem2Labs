#include "lab3UI/lab3UI.hpp"
#include "lab3UI/mySetUI.hpp"
#include "sequence/linkedListSequence.hpp"
#include "sequence/dynamicArraySequence.hpp"
#include "mySet.hpp"

namespace MySetUI 
{
    template <class T, template <class> class SequenceType>
    MySet<T, SequenceType> input()
    {
        MySet<T, SequenceType> set;

        std::cout << "Введите количество элементов" << std::endl;
        int size;
        std::cin >> size;
        
        lab3UI::printStarString();

        for (int i = 0; i < size; i++)
        {
            std::cout << "Введите элемент " << i + 1 << ":" << std::endl;
            set.Append(lab3UI::input<T>());
        }

        return set;
    }

    template <class T, template <class> class SequenceType>
    void output(MySet<T, SequenceType> set)
    {
        lab3UI::printStarString();
        std::cout << "Вывод: " << std::endl; 
        set.Map([](T element){lab3UI::output(element);});
    }

    template <class T, template <class> class SequenceType>
    void append(MySet<T, SequenceType> & set)
    {
        T input = lab3UI::input<T>();

        auto start = lab3UI::getNow();
        set.Append(input);
        lab3UI::elapsedTimeOutput(start);
    }

    template <class T, template <class> class SequenceType>
    void deleteFunc(MySet<T, SequenceType> &set)
    {
        T element;
        element = lab3UI::input<T>();

        auto start = lab3UI::getNow();
        set.Delete(element);
        lab3UI::elapsedTimeOutput(start);
    }

    template <class T, template <class> class SequenceType>
    void map(MySet<T, SequenceType> &set)
    {
        std::cout << "Прибавление ко всем элементом числа 10" << std::endl
        << "(К значению ID для Person)" << std::endl;

        auto start = lab3UI::getNow();
        set.Map([](T &element){element += 10;});
        lab3UI::elapsedTimeOutput(start);
    }

    template <class T, template <class> class SequenceType>
    void where(const MySet<T, SequenceType> &set)
    {
        std::cout << "Вывод чисел больше 10-ти" << std::endl;

        auto start = lab3UI::getNow();
        auto newSet = set.Where([](T element){return element > 10;});
        lab3UI::elapsedTimeOutput(start);

        output(newSet);
    }

    template<template<class> class SequenceType>
    void wherePerson(const MySet<Person, SequenceType> &set)
    {
        std::cout << "Вывод людей с именами начинающимися на А (английскую)" << std::endl;

        auto start = lab3UI::getNow();
        auto newSet = set.Where([](Person element) -> bool {return  (element.name.length() != 0 && element.name[0] == 'A');});
        lab3UI::elapsedTimeOutput(start);

        output(newSet);
    }

    template <>
    void where<Person, LinkedListSequence>(const MySet<Person, LinkedListSequence> &set)
    {
        wherePerson(set);
    }

    template <>
    void where<Person, DynamicArraySequence>(const MySet<Person, DynamicArraySequence> &set)
    {
        wherePerson(set);
    }

    template <class T, template <class> class SequenceType>
    void getSize(const MySet<T, SequenceType> &set)
    {
        lab3UI::printStarString();
        std::cout << set.GetSize() << std::endl;
    }

    template<class T, template<class> class SequenceType>
    void unionFunc(const MySet<T, SequenceType> &set)
    {
        MySet<T, SequenceType> inputSet = input<T, SequenceType>();

        auto start = lab3UI::getNow();
        MySet<T, SequenceType> result = set.Union(inputSet);
        lab3UI::elapsedTimeOutput(start);

        output(result);
    }

    template<class T, template<class> class SequenceType>
    void intersection(const MySet<T, SequenceType> &set)
    {
        MySet<T, SequenceType> inputSet = input<T, SequenceType>();

        auto start = lab3UI::getNow();
        MySet<T, SequenceType> result = set.Intersection(inputSet);
        lab3UI::elapsedTimeOutput(start);

        output(result);
    }

    template<class T, template<class> class SequenceType>
    void subtraction(const MySet<T, SequenceType> &set)
    {
        MySet<T, SequenceType> inputSet = input<T, SequenceType>();

        auto start = lab3UI::getNow();
        MySet<T, SequenceType> result = set.Subtraction(inputSet);
        lab3UI::elapsedTimeOutput(start);

        output(result);
    }

    template<class T, template<class> class SequenceType>
    void isSubsetOf(const MySet<T, SequenceType> &set)
    {
        MySet<T, SequenceType> inputSet = input<T, SequenceType>();

        auto start = lab3UI::getNow();
        bool result = set.IsSubsetOf(inputSet);
        lab3UI::elapsedTimeOutput(start);

        lab3UI::printStarString();
        std::cout << (result ?
            "Является подмножеством" : "Не является подмножеством") << std::endl;
    }

    template<class T, template<class> class SequenceType>
    void hasElement(const MySet<T, SequenceType> &set)
    {
        T element = lab3UI::input<T>();

        auto start = lab3UI::getNow();
        bool result = set.HasElement(element);
        lab3UI::elapsedTimeOutput(start);

        lab3UI::printStarString();
        std::cout << (result ?
            "Принадлежит множеству" : "Не принадлежит множеству") << std::endl;
    }

    template<class T, template<class> class SequenceType>
    void isEqualTo(const MySet<T, SequenceType> &set)
    {
        MySet<T, SequenceType> inputSet = input<T, SequenceType>();

        auto start = lab3UI::getNow();
        bool result = set.IsEqualTo(inputSet);
        lab3UI::elapsedTimeOutput(start);

        lab3UI::printStarString();
        std::cout << (result?
            "Множества равны" : "Множества не равны") << std::endl;
    }

    template <class T, template <class> class SequenceType>
    void menu()
    {
        std::function<void(MySet<T, SequenceType> &)> funcs[]
        {
            output<T, SequenceType>,
            append<T, SequenceType>,
            deleteFunc<T, SequenceType>,
            map<T, SequenceType>,
            where<T, SequenceType>,
            getSize<T, SequenceType>,
            unionFunc<T, SequenceType>,
            intersection<T, SequenceType>,
            subtraction<T, SequenceType>,
            isSubsetOf<T, SequenceType>,
            hasElement<T, SequenceType>,
            isEqualTo<T, SequenceType>
        };

        int funcsSize = sizeof(funcs) / sizeof(std::function<void(MySet<T, SequenceType> &)>);

        MySet<T, SequenceType> set = input<T, SequenceType>();

        while (true)
        {
            lab3UI::printStarString();
            std::cout << "Выберете команду: " << std::endl;
            std::cout << "1)\tВывод" << std::endl;
            std::cout << "2)\tAppend" << std::endl;
            std::cout << "3)\tDelete" << std::endl;
            std::cout << "4)\tMap" << std::endl;
            std::cout << "5)\tWhere" << std::endl;
            std::cout << "6)\tGetSize" << std::endl;
            std::cout << "7)\tUnion" << std::endl;
            std::cout << "8)\tIntersection" << std::endl;
            std::cout << "9)\tSubtraction" << std::endl;
            std::cout << "10)\tIsSubsetOf" << std::endl;
            std::cout << "11)\tHasElement" << std::endl;
            std::cout << "12)\tIsEqualTo" << std::endl;
            std::cout << "13)\t" << (lab3UI::autoInput ? "Выключить автоввод" : "Включить автоввод") << std::endl;
            std::cout << "14)\tВыход" << std::endl;
    
            int cmd;
            std::cin >> cmd;
    
            if (cmd >= 1 && cmd <= funcsSize)
            {
                funcs[cmd - 1](set);
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

