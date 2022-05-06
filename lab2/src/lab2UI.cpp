#include "sequence/dynamicArraySequence.hpp"
#include "sequence/linkedListSequence.hpp"

namespace Lab2UI
{
    const int starStringLen = 20;

    void inputSequence(std::unique_ptr<Sequence<int>> &sequence, int size)
    {
        for (int i = 0; i < size; i++)
        {
            int item;
            std::cin >> item;
            sequence->Append(item);
        }
    }

    Sequence<int> *sequenceOfTheSameType(std::unique_ptr<Sequence<int>> &sequence)
    {
        switch (sequence->GetType())
        {
            case SequenceType::array: return new DynamicArraySequence<int>();
            case SequenceType::list: return new LinkedListSequence<int>();
            default: return nullptr;
        }
    }

    void printStarString()
    {
        for (int i = 0; i < starStringLen; i++)
        {
            std::cout << "*";
        }

        std::cout << std::endl;
    }

    void output(std::unique_ptr<Sequence<int>> &sequence)
    {
        printStarString();
        std::cout << "Вывод: " << std::endl;

        sequence->Map([](int item){std::cout << item << " ";});
        std::cout << std::endl;
    }

    void map(std::unique_ptr<Sequence<int>> &sequence)
    {
        std::cout << "Умножение всех элементов на 2 при помощи Map" << std::endl;
        sequence->Map([](int &item){item *= 2;});
        output(sequence);
    }

    void find(std::unique_ptr<Sequence<int>> &sequence)
    {
        std::unique_ptr<Sequence<int>> subsequence(sequenceOfTheSameType(sequence));

        std::cout << "Введите размер искомой подпоследовательности" << std::endl;
        int size;
        std::cin >> size;

        std::cout << "Введите искомую подпоследовательность" << std::endl;
        inputSequence(subsequence, size);

        printStarString();
        std::cout << "индекс первого вхождения подпоследовательности: " <<
        sequence->Find(subsequence.get()) << std::endl;
    }

    void reduce(std::unique_ptr<Sequence<int>> &sequence)
    {
        int answer = sequence->Reduce([](int prev, int cur){return prev + cur;});
        std::cout << "Cумма элементов последовательности: "  << answer << std::endl;
    }

    void getFirst(std::unique_ptr<Sequence<int>> &sequence)
    {
        std::cout << sequence->GetFirst() << std::endl;
    }

    void getLast(std::unique_ptr<Sequence<int>> &sequence)
    {
        std::cout << sequence->GetLast() << std::endl;
    }

    void getSize(std::unique_ptr<Sequence<int>> &sequence)
    {
        std::cout << sequence->GetSize() << std::endl;
    }

    void getActualSize(std::unique_ptr<Sequence<int>> &sequence)
    {
        std::cout << sequence->GetActualSize() << std::endl;
    }

    void append(std::unique_ptr<Sequence<int>> &sequence)
    {
        int item;
        std::cout << "Введите число: " << std::endl;
        std::cin >> item;
        sequence->Append(item);
        output(sequence);
    }

    void prepend(std::unique_ptr<Sequence<int>> &sequence)
    {
        int item;
        std::cout << "Введите число: " << std::endl;
        std::cin >> item;
        sequence->Prepend(item);
        output(sequence);
    }

    void popBack(std::unique_ptr<Sequence<int>> &sequence)
    {
        sequence->PopBack();
        output(sequence);
    }

    void popFront(std::unique_ptr<Sequence<int>> &sequence)
    {
        sequence->PopFront();
        output(sequence);
    }

    void deleteFunc(std::unique_ptr<Sequence<int>> &sequence)
    {
        int index;
        std::cout << "Введите индекс: " << std::endl;
        std::cin >> index;
        sequence->Delete(index);
        output(sequence);
    }

    void insert(std::unique_ptr<Sequence<int>> &sequence)
    {
        int index;
        std::cout << "Введите индекс: " << std::endl;
        std::cin >> index;

        int item;
        std::cout << "Введите число: " << std::endl;
        std::cin >> item;

        sequence->InsertAt(item, index);
        output(sequence);
    }

    void where(std::unique_ptr<Sequence<int>> &sequence)
    {
        std::cout << "Получение подпоследовательности чётных чисел" << std::endl;
        std::unique_ptr<Sequence<int>> answer(sequence->Where([](int item){return item % 2 == 0;}));
        output(answer);
    }

    void concat(std::unique_ptr<Sequence<int>> &sequence)
    {
        std::unique_ptr<Sequence<int>> input(sequenceOfTheSameType(sequence));

        std::cout << "Введите количество элементов последовательности:" << std::endl;
        int size;
        std::cin >> size;

        std::cout << "Введите последовательность:" << std::endl;
        inputSequence(input, size);

        std::unique_ptr<Sequence<int>> answer(sequence->Concat(input.get()));
        output(answer);
    }

    void subsequence(std::unique_ptr<Sequence<int>> &sequence)
    {
        std::cout << "Введите индекс первого элемента" << std::endl;
        int start;
        std::cin >> start;

        std::cout << "Введите индекс последнего элемента" << std::endl;
        int end;
        std::cin >> end;

        std::unique_ptr<Sequence<int>> answer(sequence->GetSubsequence(start, end));
        output(answer);
    }

}

int main() {

    std::function<void(std::unique_ptr<Sequence<int>> &sequence)> funcs[] =
    {
            Lab2UI::map,
            Lab2UI::find,
            Lab2UI::reduce,
            Lab2UI::getFirst,
            Lab2UI::getLast,
            Lab2UI::getSize,
            Lab2UI::getActualSize,
            Lab2UI::append,
            Lab2UI::prepend,
            Lab2UI::popBack,
            Lab2UI::popFront,
            Lab2UI::deleteFunc,
            Lab2UI::insert,
            Lab2UI::where,
            Lab2UI::concat,
            Lab2UI::subsequence,
            Lab2UI::output,

    };
    const int funcsSize = sizeof(funcs) / sizeof(std::function<void(std::unique_ptr<Sequence<int>> &sequence)>);

    std::unique_ptr<Sequence<int>> sequence;

    bool typeSelected = true;
    do
    {
        std::cout << "Выберете тип последовательности: " << std::endl;
        std::cout << "1) DynamicArraySequence" << std::endl;
        std::cout << "2) LinkedListSequence" << std::endl;

        int seqType;
        std::cin >> seqType;

        switch (seqType)
        {
            case 1:
                sequence = std::unique_ptr<Sequence<int>>(new DynamicArraySequence<int>);
                break;
            case 2:
                sequence = std::unique_ptr<Sequence<int>>(new LinkedListSequence<int>);
                break;
            default:
                typeSelected = false;
                std::cout << "Неизвестная команда" << std::endl;
                break;

        }

    } while(!typeSelected);

    std::cout << "Введите количество элементов: " << std::endl;

    int size;
    std::cin >> size;

    std::cout << "Введите последовательность целых чисел: " << std::endl;

    Lab2UI::inputSequence(sequence, size);

    while (true)
    {
        Lab2UI::printStarString();

        std::cout << "Выберете команду: " << std::endl;
        std::cout << "1)\tMap" << std::endl;
        std::cout << "2)\tFind" << std::endl;
        std::cout << "3)\tReduce" << std::endl;
        std::cout << "4)\tGetFirst" << std::endl;
        std::cout << "5)\tGetLast" << std::endl;
        std::cout << "6)\tGetSize" << std::endl;
        std::cout << "7)\tGetActualSize" << std::endl;
        std::cout << "8)\tAppend" << std::endl;
        std::cout << "9)\tPrepend" << std::endl;
        std::cout << "10)\tPopBack" << std::endl;
        std::cout << "11)\tPopFront" << std::endl;
        std::cout << "12)\tDelete" << std::endl;
        std::cout << "13)\tInsertAt" << std::endl;
        std::cout << "14)\tWhere" << std::endl;
        std::cout << "15)\tConcat" << std::endl;
        std::cout << "16)\tGetSubsequence" << std::endl;
        std::cout << "17)\tВывод последовательности" << std::endl;
        std::cout << "18)\tВыход" << std::endl;

        int cmd;
        std::cin >> cmd;
        Lab2UI::printStarString();

        if (cmd >= 1 && cmd <= funcsSize)
        {
            funcs[cmd - 1](sequence);
        }
        else if (cmd == 18)
        {
            return 0;
        }
        else
        {
            std::cout << "Неизвестная команда" << std::endl;
        }
    }
}