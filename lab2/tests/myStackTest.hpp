#pragma once

#include "TestHelper.hpp"
#include "myStack.hpp"
#include "sequence/dynamicArraySequence.hpp"

template<template<typename> typename SequenceType>
void constructorFromArrFuncStack()
{
    MyStack<int, SequenceType> stack(TEST_ARR, TEST_ARR_SIZE);

    containersEqual(stack, TEST_ARR, TEST_ARR_SIZE);
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_EQ(stack.Peek(), TEST_ARR[TEST_ARR_SIZE - 1]);
    EXPECT_EQ(stack.GetSize(), TEST_ARR_SIZE);
    EXPECT_ANY_THROW(stack.operator[](stack.GetSize()));
    EXPECT_ANY_THROW(stack.operator[](-1));
}

TEST(myStackTest, constructorFromArr)
{
    constructorFromArrFuncStack<LinkedListSequence>();
    constructorFromArrFuncStack<DynamicArraySequence>();
}

template<template<typename> typename SequenceType>
void copyConstructorFuncStack()
{
    MyStack<int, SequenceType> stack1(TEST_ARR, TEST_ARR_SIZE);
    MyStack<int, SequenceType> stack2(stack1);

    containersEqual(stack1, stack2, TEST_ARR_SIZE);
    EXPECT_EQ(stack1.GetSize(), stack2.GetSize());
}

TEST(myStackTest, copyConstructor)
{
    copyConstructorFuncStack<LinkedListSequence>();
    copyConstructorFuncStack<DynamicArraySequence>();
}

template<template<typename> typename SequenceType>
void defaultConstructorFuncStack()
{
    MyStack<int, SequenceType> stack;

    EXPECT_TRUE(stack.isEmpty());
    EXPECT_ANY_THROW(stack.Peek());
}

TEST(myStackTest, defaultConstructor)
{
    defaultConstructorFuncStack<LinkedListSequence>();
    defaultConstructorFuncStack<DynamicArraySequence>();
}

template<template<typename> typename SequenceType>
void pushFuncStack()
{
    MyStack<int, SequenceType> stack(TEST_ARR, TEST_ARR_SIZE);
    int expect[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    stack.Push(8);
    containersEqual(stack, expect, ARRAY_SIZE(expect, int));
}

TEST(myStackTest, push)
{
    pushFuncStack<LinkedListSequence>();
    pushFuncStack<DynamicArraySequence>();
}

template<template<typename> typename SequenceType>
void popFuncStack()
{
    MyStack<int, SequenceType> stack(TEST_ARR, TEST_ARR_SIZE);
    int expect[] = {0, 1, 2, 3, 4, 5, 6};

    stack.Pop();

    containersEqual(stack, expect, ARRAY_SIZE(expect, int));
    EXPECT_EQ(stack.GetSize(), ARRAY_SIZE(expect, int));
}

TEST(myStackTest, pop)
{
    popFuncStack<LinkedListSequence>();
    popFuncStack<DynamicArraySequence>();
}

template<template<typename> typename SequenceType>
void map1FuncStack()
{
    MyStack<int, SequenceType> stack(TEST_ARR, TEST_ARR_SIZE);
    int expect[] = {0 * 2, 1 * 2, 2 * 2, 3 * 2, 4 * 2, 5 * 2, 6 * 2,7 * 2};

    stack.Map([](int &item){item *= 2;});

    containersEqual(stack, expect, ARRAY_SIZE(expect, int));
    EXPECT_EQ(stack.GetSize(), TEST_ARR_SIZE);
}

TEST(myStackTest, map1)
{
    map1FuncStack<LinkedListSequence>();
    map1FuncStack<DynamicArraySequence>();
}

template<template<typename> typename SequenceType>
void map2FuncStack()
{
    MyStack<int, SequenceType> stack(TEST_ARR, TEST_ARR_SIZE);
    int expect[] = {0, 1, 2 * 2, 3 * 2, 4 * 2, 5 * 2, 6,7};

    stack.Map([](int &item){item *= 2;}, 2, 5);

    containersEqual(stack, expect, ARRAY_SIZE(expect, int));
    EXPECT_EQ(stack.GetSize(), TEST_ARR_SIZE);
}

TEST(myStackTest, map2)
{
    map2FuncStack<LinkedListSequence>();
    map2FuncStack<DynamicArraySequence>();
}

template<template<typename> typename SequenceType>
void mapExceptionFuncStack()
{
    MyStack<int, SequenceType> stack(TEST_ARR, TEST_ARR_SIZE);

    EXPECT_ANY_THROW(stack.Map([](int &item){}, -1, 0));
    EXPECT_ANY_THROW(stack.Map([](int &item){}, 8, 0));
    EXPECT_ANY_THROW(stack.Map([](int &item){}, 0, -1));
    EXPECT_ANY_THROW(stack.Map([](int &item){}, 0, 8));
    EXPECT_ANY_THROW(stack.Map([](int &item){}, 5, 3));
}

TEST(myStackTest, map3)
{
    mapExceptionFuncStack<LinkedListSequence>();
    mapExceptionFuncStack<DynamicArraySequence>();
}

template<template<typename> typename SequenceType>
void concatFuncStack()
{
    int arr1[] = {0, 1, 2};
    int arr2[] = {3, 4, 5, 6, 7};

    MyStack<int, SequenceType> stack1(arr1, ARRAY_SIZE(arr1, int));
    MyStack<int, SequenceType> stack2(arr2, ARRAY_SIZE(arr2, int));
    auto stack3 = stack1.Concat(stack2);

    containersEqual(stack3, TEST_ARR, TEST_ARR_SIZE);
    EXPECT_EQ(stack3.GetSize(), TEST_ARR_SIZE);
}

TEST(myStackTest, concat)
{
    concatFuncStack<LinkedListSequence>();
    concatFuncStack<DynamicArraySequence>();
}

template<template<typename> typename SequenceType>
void find1FuncStack()
{
    int arr[] = {2, 3, 4};
    MyStack<int, SequenceType> stack(TEST_ARR, TEST_ARR_SIZE);
    MyStack<int, SequenceType> subStack(arr, ARRAY_SIZE(arr, int));

    EXPECT_EQ(stack.Find(subStack), 2);
}

TEST(myStackTest, find1)
{
    find1FuncStack<LinkedListSequence>();
    find1FuncStack<DynamicArraySequence>();
}

template<template<typename> typename SequenceType>
void find2FuncStack()
{
    int arr[] = {1, 2, 3};
    MyStack<int, SequenceType> subStack(arr, ARRAY_SIZE(arr, int));
    auto stack = subStack.Concat(subStack);

    EXPECT_EQ(stack.Find(subStack, stack.Find(subStack) + 1), 3);
}

TEST(myStackTest, find2)
{
    find2FuncStack<LinkedListSequence>();
    find2FuncStack<DynamicArraySequence>();
}

template<template<typename> typename SequenceType>
void subsequenceFuncStack()
{
    MyStack<int, SequenceType> stack(TEST_ARR, TEST_ARR_SIZE);
    int expected[] = {1, 2, 3};

    auto subStack = stack.GetSubsequence(1, 3);

    containersEqual(subStack, expected, ARRAY_SIZE(expected, int));
    EXPECT_EQ(subStack.GetSize(), ARRAY_SIZE(expected, int));
}

TEST(myStackTest, substack)
{
    subsequenceFuncStack<LinkedListSequence>();
    subsequenceFuncStack<DynamicArraySequence>();
}

template<template<typename> typename SequenceType>
void whereFuncStack()
{
    MyStack<int, SequenceType> stack(TEST_ARR, TEST_ARR_SIZE);
    int expected[] = {1, 2, 3};

    MyStack<int, SequenceType> subStack = stack.Where([](int item) -> bool {return item >= 1 && item <= 3;});

    containersEqual(subStack, expected, ARRAY_SIZE(expected, int));
    EXPECT_EQ(subStack.GetSize(), ARRAY_SIZE(expected, int));
}

TEST(myStackTest, where)
{
    whereFuncStack<LinkedListSequence>();
    whereFuncStack<DynamicArraySequence>();
}

template<template<typename> typename SequenceType>
void reduceFuncStack()
{
    MyStack<int, SequenceType> stack(TEST_ARR, TEST_ARR_SIZE);
    int expected = (1 + 2 + 3 + 4 + 5 + 6 + 7) * 10;

    int reduced = stack.Reduce([](int prev, int cur) -> int {return prev + cur * 10;});

    EXPECT_EQ(reduced, expected);
}

TEST(myStackTest, reduce)
{
    reduceFuncStack<LinkedListSequence>();
    reduceFuncStack<DynamicArraySequence>();
}