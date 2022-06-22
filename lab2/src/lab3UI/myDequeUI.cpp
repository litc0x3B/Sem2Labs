#include "lab3UI/lab3UI.hpp"
#include "lab3UI/myDequeUI.hpp"
#include "sequence/linkedListSequence.hpp"
#include "sequence/dynamicArraySequence.hpp"
#include "sequence/sequence.hpp"
#include "myDeque.hpp"

namespace MyDequeUI 
{   
    template <class T, template <class> class SequenceType>
    MyDeque<T, SequenceType> input()
    {
        std::cout << "Введите размер стека: " << std::endl;
        int size;
        std::cin >> size;

        MyDeque<T, SequenceType> deque;

        for (int i = 0; i < size; i++)
        {
            std::cout << "Введите значание " << i + 1 << ":" << std::endl;
            T item = lab3UI::input<T>();
            deque.PushBack(item);
        }

        return deque;
    }

    template <class T, template <class> class SequenceType>
    void output(MyDeque<T, SequenceType> & deque)
    {
        lab3UI::printStarString();
        std::cout << "Вывод: " << std::endl;
        deque.Map([](T item){lab3UI::output(item);});
    }

    template <class T, template <class> class SequenceType>
    void getSize(MyDeque<T, SequenceType> & deque)
    {
        lab3UI::printStarString();
        std::cout << "Вывод: " << deque.GetSize() << std::endl;
    }

    template <class T, template <class> class SequenceType>
    void isEmpty(MyDeque<T, SequenceType> & deque)
    {
        lab3UI::printStarString();
        std::cout << (deque.isEmpty() ? "Дек пуст" : "Дек не пуст") << std::endl;
    }

    template <class T, template <class> class SequenceType>
    void back(MyDeque<T, SequenceType> & deque)
    {
        lab3UI::printStarString();
        lab3UI::output(deque.Back());
    }

    template <class T, template <class> class SequenceType>
    void front(MyDeque<T, SequenceType> & deque)
    {
        lab3UI::printStarString();
        lab3UI::output(deque.Front());
    }
    
    template <class T, template <class> class SequenceType>
    void reduce(MyDeque<T, SequenceType> & deque)
    {
        lab3UI::printStarString();
        std::cout << "Вывод максимального значения" << std::endl
             << "(для Person лексикографическое сравнение по имени)" << std::endl;

        auto start = lab3UI::getNow();
        T max = deque.Reduce([](T prev, T cur){return prev > cur ? prev : cur;});
        lab3UI::elapsedTimeOutput(start);
        
        lab3UI::printStarString();
        lab3UI::output(max);
    }

    template <class T, template <class> class SequenceType>
    void find(MyDeque<T, SequenceType> & deque)
    {
        std::cout << "Введите подпоследовательность: " << std::endl;
        auto subdeque = input<T, SequenceType>();

        auto start = lab3UI::getNow();
        int result = deque.Find(subdeque);
        lab3UI::elapsedTimeOutput(start);

        lab3UI::printStarString();
        std::cout << "Индекс первого вхождения: " << result << std::endl;
    }

    template <class T, template <class> class SequenceType>
    void pushBack(MyDeque<T, SequenceType> & deque)
    {
        T item = lab3UI::input<T>();

        auto start = lab3UI::getNow();
        deque.PushBack(item);
        lab3UI::elapsedTimeOutput(start);
    }

    template <class T, template <class> class SequenceType>
    void pushFront(MyDeque<T, SequenceType> & deque)
    {
        T item = lab3UI::input<T>();

        auto start = lab3UI::getNow();
        deque.PushFront(item);
        lab3UI::elapsedTimeOutput(start);
    }

    template <class T, template <class> class SequenceType>
    void popBack(MyDeque<T, SequenceType> & deque)
    {
        auto start = lab3UI::getNow();
        deque.PopBack();
        lab3UI::elapsedTimeOutput(start);
    }

    template <class T, template <class> class SequenceType>
    void popFront(MyDeque<T, SequenceType> & deque)
    {
        auto start = lab3UI::getNow();
        deque.PopFront();
        lab3UI::elapsedTimeOutput(start);
    }

    template <class T, template <class> class SequenceType>
    void map(MyDeque<T, SequenceType> & deque)
    {
        std::cout << "Увеличение каждого числа на 10" << std::endl;
        std::cout << "(для Person увеличение ID)" << std::endl;

        auto start = lab3UI::getNow();
        deque.Map([](T &item){item += 10;});
        lab3UI::elapsedTimeOutput(start);
    }

    template <class T, template <class> class SequenceType>
    void where(MyDeque<T, SequenceType> & deque)
    {
        std::cout << "Составление стека, в котором все числа больше 10-ти" << std::endl;

        auto start = lab3UI::getNow();
        auto result = deque.Where([](T item){return item > 10;});
        lab3UI::elapsedTimeOutput(start);

        output(result);
    }

    template< template<class> class SequenceType>
    void wherePerson(MyDeque<Person, SequenceType> &deque)
    {
        std::cout << "Вывод элементов с именами начинающимися на 'A' (английскую)" << std::endl;

        auto start = lab3UI::getNow();
        auto result = deque.Where([](Person item){return item.name.length() != 0 && item.name[0] == 'A';});
        lab3UI::elapsedTimeOutput(start);

        output(result);
    }

    template<> void where<Person, DynamicArraySequence>(MyDeque<Person, DynamicArraySequence> & deque)
    {
        wherePerson(deque);
    }

    template<> void where<Person, LinkedListSequence>(MyDeque<Person, LinkedListSequence> & deque)
    {
        wherePerson(deque);
    }

    template<class T, template<class> class SequenceType>
    void getSubsequence(MyDeque<T, SequenceType> & deque)
    {
        std::cout << "Введите индекс первого элемента (начиная с нуля)" << std::endl;
        int startIndex;
        std::cin >> startIndex;

        std::cout << "Введите индекс последнего элемента (начиная с нуля)" << std::endl;
        int endIndex;
        std::cin >> endIndex;

        auto start = lab3UI::getNow();
        auto result = deque.GetSubsequence(startIndex, endIndex);
        lab3UI::elapsedTimeOutput(start);

        output(result);
    }

    template<class T, template<class> class SequenceType>
    void concat(MyDeque<T, SequenceType> & deque)
    {
        auto inputDeque = input<T, SequenceType>();

        auto start = lab3UI::getNow();
        auto result = deque.Concat(inputDeque);
        lab3UI::elapsedTimeOutput(start);

        output(result);
    }

    template <class T, template <class> class SequenceType>
    void menu()
    {
        std::function<void(MyDeque<T, SequenceType> &)> funcs[]
        {
            output<T, SequenceType>,
            getSize<T, SequenceType>,
            isEmpty<T, SequenceType>,
            back<T, SequenceType>,
            front<T, SequenceType>,
            reduce<T, SequenceType>,
            find<T, SequenceType>,
            pushBack<T, SequenceType>,
            pushFront<T, SequenceType>,
            popBack<T, SequenceType>,
            popFront<T, SequenceType>,
            map<T, SequenceType>,
            where<T, SequenceType>,
            getSubsequence<T, SequenceType>,
            concat<T, SequenceType>
        };

        int funcsSize = sizeof(funcs) / sizeof(std::function<void(MyDeque<T, SequenceType> &)>);

        MyDeque<T, SequenceType> deque = input<T, SequenceType>();

        while (true)
        {
            lab3UI::printStarString();
            std::cout << "Выберете команду: " << std::endl;
            std::cout << "1)\tВывод" << std::endl;
            std::cout << "2)\tGetSize" << std::endl;
            std::cout << "3)\tisEmpty" << std::endl;
            std::cout << "4)\tBack" << std::endl;
            std::cout << "5)\tFront" << std::endl;
            std::cout << "6)\tReduce" << std::endl;
            std::cout << "7)\tFind" << std::endl;
            std::cout << "8)\tPushBack" << std::endl;
            std::cout << "9)\tPushFront" << std::endl;
            std::cout << "10)\tPopBack" << std::endl;
            std::cout << "11)\tPopFront" << std::endl;
            std::cout << "12)\tMap" << std::endl;
            std::cout << "13)\tWhere" << std::endl;
            std::cout << "14)\tGetSubsequence" << std::endl;
            std::cout << "15)\tConcat" << std::endl;
            std::cout << "16)\t" << (lab3UI::autoInput ? "Выключить автоввод" : "Включить автоввод") << std::endl;
            std::cout << "17)\tВыход" << std::endl;
    
            int cmd;
            std::cin >> cmd;
    
            if (cmd >= 1 && cmd <= funcsSize)
            {
                funcs[cmd - 1](deque);
            }
            else if(cmd == 16)
            {
                lab3UI::autoInput = !lab3UI::autoInput;
            }
            else if(cmd == 17)
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