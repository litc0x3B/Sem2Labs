#include <gtest/gtest.h>

#include "linkedListTest.hpp"
#include "sequence/linkedListSequenceTest.hpp"
#include "sequence/dynamicArraySequenceTest.hpp"
#include "myStackTest.hpp"

int main()
{
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
    return 0;
}