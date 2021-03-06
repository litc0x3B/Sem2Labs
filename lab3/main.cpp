#include "binTree.hpp"
#include "set.hpp"
#include "priorityQueue.hpp"
#include "icollection.hpp"

#include <cstdio>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <chrono>

void pressAnyKey()
{
    std::cout << "Нажмите любую клавишу для продолжения..." << std::endl;
    getchar();
}

int toIntFunc(std::string str)
{
    return stoi(str);
}

template<class T>
void resultFunc(T collection)
{
    std::cout << "Результат: ";
    std::cout <<  collection.ToStr() << std::endl;
}

template<>
void resultFunc(ICollection<int> *collection)
{
    std::cout << "Результат: ";
    std::cout <<  collection->ToStr() << std::endl;
}

template<>
void resultFunc(PriorityQueue<int> queue)
{
    std::cout << "Результат: ";
    queue.Map([](int item)
    {
        std::cout << item << " ";
        return item;
    });

    std::cout << std::endl;
}


void speedTest()
{
    std::cout << "****************************"<< std::endl;
    std::cout << "Проверка скорости выполнения" << std::endl;

    BinTree<int> tree;
    int size = 10000000;

    
    std::cout << "Создание дерева с " << size << " элементами (может занять некторое время)" << std::endl;
    for (int i = 0; i < size; i++)
    {
        tree.Add(i);
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    tree.Add(size);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Вставка одного элемента заняла " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " [ns]" << std::endl;

    begin = std::chrono::steady_clock::now();
    tree.Search(size);
    end = std::chrono::steady_clock::now();
    std::cout << "Поиск одного элемента занял " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " [ns]" << std::endl;

    begin = std::chrono::steady_clock::now();
    tree.Remove(size);
    end = std::chrono::steady_clock::now();
    std::cout << "Удаление одного элемента заняло " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " [ns]" << std::endl;

    pressAnyKey();
}

void icollectionTest(ICollection<int> *collection)
{
    std::cout << "Вставка элементов из строки: 1 2 3 4 5 6" << std::endl;
    collection->AddFromStr(toIntFunc, "1 2 3 4 5 6");
    resultFunc(collection);

    std::cout << "Вставка одного элемента (7)" << std::endl;
    collection->Add(7);
    resultFunc(collection);

    std::cout << "Удаление элемента (4)" << std::endl;
    collection->Remove(4);
    resultFunc(collection);

    std::cout << "Поиск элемента (3)" << std::endl;
    std::cout << (collection->Search(3) ? "Найден" : "Не наёден") << std::endl;

    std::cout << "Поиск элемента (4)" << std::endl;
    std::cout << (collection->Search(4) ? "Найден" : "Не наёден") << std::endl;

    std::cout << "Увелечение всех элементов на 1 при помощи Map()" << std::endl;
    std::unique_ptr<ICollection<int>> collectionMap(collection->MapC([](int item){return item + 1;}));
    resultFunc(collectionMap.get());

    std::cout << "получение коллекции с элементами < 5" << std::endl;
    std::unique_ptr<ICollection<int>> collectionWhere(collection->WhereC([](int item){return item < 5;}));
    resultFunc(collectionWhere.get());

    std::cout << "Получение суммы элементов" << std::endl;
    int sum = collection->Reduce([](int prev, int cur){return prev + cur;}, 0);
    std::cout << "Результат: " << sum << std::endl;

    pressAnyKey();
}

void treeTest()
{
    std::cout << "Создание дерева без баллансировки:" << std::endl;
    std::cout << "                      10" << std::endl;
    std::cout << "                   /       \\" << std::endl;
    std::cout << "                 8          13" << std::endl;
    std::cout << "               /   \\       /   \\" << std::endl;
    std::cout << "             7     9     11    14" << std::endl;
    std::cout << "                           \\" << std::endl;
    std::cout << "                            12" << std::endl << std::endl;

    BinTree<int> tree;
    tree.SetRandomlyBalanced(false);
    tree.Add(10);
    tree.Add(8);
    tree.Add(9);
    tree.Add(13);
    tree.Add(14);
    tree.Add(7);
    tree.Add(11);
    tree.Add(12);

    std::cout << "Извлечение поддерева с корнем 13" << std::endl;
    auto subtree = tree.GetSubtree(13);
    resultFunc(tree.GetSubtree(13));

    std::cout << "Поиск извлечённого поддерева" << std::endl;
    std::cout << (tree.HasSubtree(subtree) ? "Найдено" : "Не найдено") << std::endl;

    std::cout << "Удалим элемент 11 из полученного поддерева проверим снова" <<std::endl;
    subtree.Remove(11);
    std::cout << (tree.HasSubtree(subtree) ? "Найдено" : "Не найдено") << std::endl;

    std::cout << "Сохранение в строку при обходе 'КЛП'" << std::endl;
    std::cout << "Результат: " << tree.ToStr(" ", "NLR") << std::endl;

    std::cout << "Сохранение в строку при обходе 'ПКЛ'" << std::endl;
    std::cout << "Результат: " << tree.ToStr(" ", "RNL") << std::endl;
    pressAnyKey();
}

void setTest()
{
    std::cout << "Два множества: 1 2 3 4 и 3 4 5 6" << std::endl;
    Set<int> set1(toIntFunc, "1 2 3 4");
    Set<int> set2(toIntFunc, "3 4 5 6");

    std::cout << "Пересечение" << std::endl;
    resultFunc(set1 * set2);

    std::cout << "Объединение" << std::endl;
    resultFunc(set1 + set2);
    
    std::cout << "Вычитание" << std::endl;
    resultFunc(set1 - set2);

    std::cout << "Сравнение множетв" << std::endl;
    std::cout << ( set1 == set2 ? "Они равны" : "Они не равны") << std::endl;

    std::cout << "Является ли множество один подмножеством множества два" << std::endl;
    std::cout << ( set2.Has(set1) ? "Является" : "Не является") << std::endl;

    std::cout << "Сравнение множетв 1 2 3 и 1 2 3" << std::endl;
    std::cout << ( Set<int>(toIntFunc, "1 2 3") == Set<int>(toIntFunc, "1 2 3") ? "Они равны" : "Они не равны") << std::endl;

    std::cout << "Является ли множество 2 3 подмножеством множества 1 2 3 4" << std::endl;
    std::cout << ( set1.Has(Set<int>(toIntFunc, "2 3")) ? "Является" : "Не является") << std::endl;
    
    pressAnyKey();
}

void queueTest()
{
    std::cout << "****************************"<< std::endl;
    std::cout << "Тест очереди с приоритетами:"<< std::endl;

    PriorityQueue<int> queue;

    std::cout << "Создадим очередь и добавим в неё следующие элементы (число, приоритет)" << std::endl;
    std::cout << "(30, 3), (10, 1), (50, 5), (40, 4), (20, 2)" << std::endl;
    queue.Push(30, 3);
    queue.Push(10, 1);
    queue.Push(50, 5);
    queue.Push(40, 4);
    queue.Push(20,2);

    std::cout << "Посмотрим на элемент с максимальным приоритетом" << std::endl;
    std::cout << queue.Peek() << std::endl;

    std::cout << "Извлечём элемент с максимальным приоритетом" << std::endl;
    std::cout << queue.Pop() << std::endl;

    std::cout << "Ещё раз посмотрим на элемент с максимальным приоритетом" << std::endl;
    std::cout << queue.Peek() << std::endl;

    std::cout << "Увелечение всех элементов на 1 при помощи Map()" << std::endl;
    resultFunc(queue.Map([](int item){return item + 1;}));

    std::cout << "Получение очереди с элементами < 40" << std::endl;
    resultFunc(queue.Where([](int item){return item < 40;}));

    std::cout << "Получение суммы элементов" << std::endl;
    int sum = queue.Reduce([](int prev, int cur){return prev + cur;}, 0);
    std::cout << "Результат: " << sum << std::endl;

    std::cout << "Поиск на вхождение очереди (30, 3), (40, 4)" << std::endl;
    PriorityQueue<int> queue1;
    queue1.Push(30, 3);
    queue1.Push(40, 4);
    std::cout << (queue.Search(queue1) ? "Входит" : "Не входит") << std::endl;

    std::cout << "Поиск на вхождение очереди (10, 1), (40, 4)" << std::endl;
    PriorityQueue<int> queue2;
    queue2.Push(10, 1);
    queue2.Push(40, 4);
    std::cout << (queue.Search(queue2) ? "Входит" : "Не входит") << std::endl;

   pressAnyKey();
}

void treeTestFull()
{
    std::cout << "****************************"<< std::endl;
    std::cout << "Тест бинарого дерева:"<< std::endl;
    BinTree<int> tree;
    icollectionTest(&tree);
    treeTest();
}

void setTestFull()
{
    std::cout << "****************************"<< std::endl;
    std::cout << "Тест множества:"<< std::endl;
    Set<int> set; 
    icollectionTest(&set);
    setTest();
}

int main()
{    
    // treeTestFull();
    // setTestFull();
    queueTest();
    // speedTest();
}