#include "test_binTree.hpp"
#include "test_set.hpp"

#include <functional>
#include <gtest/gtest.h>
#include <iostream>
#include <climits>
#include <memory>
#include <string>

void stressTest()
{

    BinTree<int> tree;

    for (int i = 0; i < 100000; i++)
    {
        tree.Add(i);
    }

    std::cout << tree.Search(1000000) << std::endl;
}

int main()
{
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
}
