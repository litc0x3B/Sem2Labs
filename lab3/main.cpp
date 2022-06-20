#include "binTree.hpp"
#include "set.hpp"
#include "priorityQueue.hpp"
#include "icollection.hpp"
#include <cstdio>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>

void stressTest()
{

    BinTree<int> tree;

    for (int i = 0; i < 100000; i++)
    {
        tree.Add(i);
    }
}

void pressAnyKey()
{
    std::cout << "Нажмите любую клавишу для продолжения" << std::endl;
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

    std::cout << "Получение суммы элиментов" << std::endl;
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

    pressAnyKey();
}


int main()
{
    BinTree<int> tree;
    Set<int> set; 

    icollectionTest(&tree);
    treeTest();
    icollectionTest(&set);
    setTest();
}