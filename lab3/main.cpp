#include <iostream>
#include "binTree.hpp"
#include <climits>


void stressTest()
{

    BinTree<int> tree;

    for (int i = 0; i < 100000; i++)
    {
        tree.Insert(i);
    }

    std::cout << tree.Search(1000000) << std::endl;
    //tree.Traverse([] (int value) {std::cout << value << std::endl;}, "NLR");
}


int main()
{
    // BinTree<int> tree1;
    // tree1.Insert(5);
    // tree1.Insert(28);
    // tree1.Insert(10);
    // tree1.Insert(515);
    // tree1.Insert(75);
    // tree1.Insert(8);
    // tree1.Insert(4);
    // tree1.Traverse([] (int value) {std::cout << value << std::endl;});

    // std::cout << "******" << std::endl;
    // auto tree2 = tree1.Map([](int value){return value * 10;});
    // tree2.Traverse([] (int value) {std::cout << value << std::endl;});

    // std::cout << "******" << std::endl;
    // BinTree<int> tree3;
    // tree3 = tree1.Where([](const int &value){return value <= 100;});
    // tree3.Traverse([] (int value) {std::cout << value << std::endl;});
    
    // std::cout << "done!" << std::endl;

    // int found;
    // std::cout << tree1.Search(75, found) << " " << found << " " << tree1.Search(1) << std::endl;

    stressTest();
}
