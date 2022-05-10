#pragma once

#include "mySet.hpp"
#include "TestHelper.hpp"
#include "sequence/dynamicArraySequence.hpp"
#include "sequence/linkedListSequence.hpp"
#include "sequence/sequence.hpp"
#include <gtest/gtest.h>
#include <ostream>

namespace MySetTest
{
    const int INIT_ARR1[] = {0, 1, 2, 3};
    const int INIT_ARR2[] = {2, 3, 4, 5, 6, 7};

    const MySet<int, DynamicArraySequence> set1Array(INIT_ARR1, ARRAY_SIZE(INIT_ARR1, int));
    const MySet<int, DynamicArraySequence> set2Array(INIT_ARR2, ARRAY_SIZE(INIT_ARR2, int));
    const MySet<int, LinkedListSequence> set1List(INIT_ARR1, ARRAY_SIZE(INIT_ARR1, int));
    const MySet<int, LinkedListSequence> set2List(INIT_ARR2, ARRAY_SIZE(INIT_ARR2, int));

    template <template<class> class SequenceType>
    void ExpectEqualToArray(const int *arr, const MySet<int, SequenceType> set, int size)
    {
        EXPECT_EQ(size, set.GetSize());

        for (int i = 0; i < size; i++)
        {
            EXPECT_TRUE(set.HasElement(arr[i])) << "Index: " << i << std::endl 
            << "Were looking for element: " << arr[i] << std::endl;
        }
    }
}

TEST(MySet, unionTest)
{
    MySetTest::ExpectEqualToArray
    (
        TEST_ARR, 
        MySetTest::set1Array.Union(MySetTest::set2Array), 
        TEST_ARR_SIZE
    );

    MySetTest::ExpectEqualToArray
    (
        TEST_ARR, 
        MySetTest::set1List.Union(MySetTest::set2List), 
        TEST_ARR_SIZE
    );
}

TEST(MySet, intersection)
{
    int expect[] = {2, 3};

    MySetTest::ExpectEqualToArray
    (
        expect, 
        MySetTest::set1Array.Intersection(MySetTest::set2Array), 
        ARRAY_SIZE(expect, int)
    );

    MySetTest::ExpectEqualToArray
    (
        expect, 
        MySetTest::set1List.Intersection(MySetTest::set2List), 
        ARRAY_SIZE(expect, int)
    );
}


TEST(MySet, subtraction)
{
    int expect[] = {0, 1};

    MySetTest::ExpectEqualToArray
    (
        expect, 
        MySetTest::set1Array.Subtraction(MySetTest::set2Array), 
        ARRAY_SIZE(expect, int)
    );

    MySetTest::ExpectEqualToArray
    (
        TEST_ARR, 
        MySetTest::set1List.Subtraction(MySetTest::set2List), 
        ARRAY_SIZE(expect, int)
    );
}


TEST(MySet, isSubset)
{
    int arr[] = {0, 1};
    MySet<int, DynamicArraySequence> subsetArr(arr,
        ARRAY_SIZE(arr, int));

    MySet<int, LinkedListSequence> subsetList(arr,
        ARRAY_SIZE(arr, int));
    
    EXPECT_TRUE(subsetList.IsSubsetOf(MySetTest::set1List));
    EXPECT_FALSE(subsetList.IsSubsetOf(MySetTest::set2List));

    EXPECT_TRUE(subsetArr.IsSubsetOf(MySetTest::set1Array));
    EXPECT_FALSE(subsetArr.IsSubsetOf(MySetTest::set2Array));
}

TEST(MySet, areEqual)
{
    MySet<int, DynamicArraySequence> set1ArrayCopy(MySetTest::set1Array);
    MySet<int, LinkedListSequence> set1ListCopy(MySetTest::set1List);

    EXPECT_TRUE(set1ListCopy.IsEqualTo(MySetTest::set1List));
    EXPECT_FALSE(set1ListCopy.IsEqualTo(MySetTest::set2List));

    EXPECT_TRUE(set1ArrayCopy.IsEqualTo(MySetTest::set1Array));
    EXPECT_FALSE(set1ArrayCopy.IsEqualTo(MySetTest::set2Array));
}

TEST(MySet, appendSucces)
{
    MySet<int, DynamicArraySequence> setArr(MySetTest::set1Array);
    MySet<int, LinkedListSequence> setList(MySetTest::set1List);
    int expect[] = {0, 1, 2, 3, 4};

    EXPECT_TRUE(setArr.Append(4));
    MySetTest::ExpectEqualToArray(expect, setArr, ARRAY_SIZE(expect, int));

    EXPECT_TRUE(setList.Append(4));
    MySetTest::ExpectEqualToArray(expect, setList, ARRAY_SIZE(expect, int));
}

TEST(MySet, appendFailure)
{
    MySet<int, DynamicArraySequence> setArr(MySetTest::set1Array);
    MySet<int, LinkedListSequence> setList(MySetTest::set1List);
    int expect[] = {0, 1, 2, 3};

    EXPECT_FALSE(setArr.Append(3));
    MySetTest::ExpectEqualToArray(expect, setArr, ARRAY_SIZE(expect, int));

    EXPECT_FALSE(setList.Append(3));
    MySetTest::ExpectEqualToArray(expect, setList, ARRAY_SIZE(expect, int));
}

TEST(MySet, deleteTest)
{
    MySet<int, DynamicArraySequence> setArr(MySetTest::set1Array);
    MySet<int, LinkedListSequence> setList(MySetTest::set1List);
    int expect[] = {0, 1, 3};

    setArr.Delete(2);
    MySetTest::ExpectEqualToArray(expect, setArr, ARRAY_SIZE(expect, int));

    setList.Delete(2);
    MySetTest::ExpectEqualToArray(expect, setList, ARRAY_SIZE(expect, int));
}

TEST(MySet, map)
{
    MySet<int, DynamicArraySequence> setArr(MySetTest::set2Array);
    MySet<int, LinkedListSequence> setList(MySetTest::set2List);
    int expect[] = {2 * 2, 3 * 2, 4 * 2, 5 * 2, 6 * 2, 7 * 2};

    setArr.Map([](int &element){element *= 2;});
    MySetTest::ExpectEqualToArray(expect, setArr, ARRAY_SIZE(expect, int));

    setList.Map([](int &element){element *= 2;});
    MySetTest::ExpectEqualToArray(expect, setList, ARRAY_SIZE(expect, int));
}

TEST(MySet, where)
{
    int expect[] = {2, 4, 6};

    MySet<int, DynamicArraySequence> setArr = MySetTest::set2Array.Where([](int element){return element % 2 == 0;});
    MySetTest::ExpectEqualToArray(expect, setArr, ARRAY_SIZE(expect, int));

    MySet<int, LinkedListSequence> setList =  MySetTest::set2List.Where([](int element){return element % 2 == 0;});
    MySetTest::ExpectEqualToArray(expect, setList, ARRAY_SIZE(expect, int));
}