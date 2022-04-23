#pragma once
#include "TestHelper.hpp"
#include "linkedList.hpp"

TEST(LinkedList, DefaultConstructorAndAppend) {
    LinkedList<int> list;
    list.Append(10);
    list.Append(15);

    int arr[] = {10, 15};
    int size = ARRAY_SIZE(arr, int);

    containersEqual(list, arr, size);
    EXPECT_EQ(list.GetSize(), size);
}

TEST(LinkedList, DefaultConstructorAndPrepend) {
    LinkedList<int> list;
    list.Prepend(10);
    list.Prepend(15);

    int arr[] = {15, 10};
    int size = ARRAY_SIZE(arr, int);

    containersEqual(list, arr, size);
    EXPECT_EQ(list.GetSize(), size);
}

TEST(LinkedList, ListFromArray) {
    int arr[] = {1, 2, 3, 4, 5};
    int size = ARRAY_SIZE(arr, int);

    LinkedList<int> list(arr, size);

    containersEqual(list, arr, size);
    EXPECT_EQ(list.GetSize(), size);
}

TEST(LinkedList, CopyingConstructorTest) {
    int arr[] = {156, 40, 150, 445645, 7, 15, 66565};
    int size = ARRAY_SIZE(arr, int);

    LinkedList<int> list1(arr, size);
    LinkedList<int> list2 = list1;

    containersEqual(list2, list1, size);
    EXPECT_EQ(list2.GetSize(), list1.GetSize());
  }

TEST(LinkedList, DestructonWithoutElements) { LinkedList<int> list; }

TEST(LinkedList, DestructonWithOneElement) {
    LinkedList<int> list;
    list.Append(0);
}

TEST(LinkedList, Concat) {
    int arr1[] = {6, 9};
    int arr2[] = {7, 2, 7};
    int result[] = {6, 9, 7, 2, 7};

    int arr1Size = ARRAY_SIZE(arr1, int);
    int arr2Size = ARRAY_SIZE(arr2, int);

    LinkedList<int> list1(arr1, arr1Size);
    LinkedList<int> list2(arr2, arr2Size);
    LinkedList<int> resultList = list1 + list2;

    containersEqual(resultList, result, arr1Size + arr2Size);
    EXPECT_EQ(resultList.GetSize(), arr1Size + arr2Size);
  }

TEST(LinkedList, Assignment1) {
    int arr[] = {4544, 798634, 78988, 454};
    int size = ARRAY_SIZE(arr, int);

    LinkedList<int> list1;
    LinkedList<int> list2(arr, size);
    list1 = list2;

    containersEqual(list1, list2, list1.GetSize());
    EXPECT_EQ(list1.GetSize(), list2.GetSize());
  }

TEST(LinkedList, Assignment2) {
    int arr1[] = {4544, 798634, 78988, 454};
    int arr2[] = {9, 9, 9, 9, 9, 9, 9};

    int size1 = ARRAY_SIZE(arr1, int);
    int size2 = ARRAY_SIZE(arr2, int);

    LinkedList<int> list1(arr1, size1);
    LinkedList<int> list2(arr2, size2);
    list1 = list2;

    containersEqual(list1, list2, list1.GetSize());
    EXPECT_EQ(list1.GetSize(), list2.GetSize());
  }

TEST(LinkedList, Assignment3) {
    int arr1[] = {4544, 798634, 78988, 454};
    int arr2[] = {9, 9, 9, 9, 9, 9, 9};

    int size1 = ARRAY_SIZE(arr1, int);
    int size2 = ARRAY_SIZE(arr2, int);

    LinkedList<int> list1(arr1, size1);
    LinkedList<int> list2(arr2, size2);
    list2 = list1;

    containersEqual(list2, list1, list1.GetSize());
    EXPECT_EQ(list1.GetSize(), list2.GetSize());
}

TEST(LinkedList, Assignment4) {
    int arr[] = {4544, 798634, 78988, 454};
    int size = ARRAY_SIZE(arr, int);

    LinkedList<int> list1;
    LinkedList<int> list2(arr, size);
    list2 = list1;

    containersEqual(list2, list1, list1.GetSize());
    EXPECT_EQ(list1.GetSize(), list2.GetSize());
}

TEST(LinkedList, Assignment5) {
    int arr[] = {4544, 798634, 78988, 454};
    int size = ARRAY_SIZE(arr, int);

    LinkedList<int> list(arr, size);
    list = list;

    containersEqual(list, arr, size);
    EXPECT_EQ(list.GetSize(), size);
}

TEST(LinkedList, PopBack1) {
    int arr[] = {4544, 798634, 78988, 454};
    int result[] = {4544, 798634, 78988};

    int size = ARRAY_SIZE(arr, int);
    int resultSize = ARRAY_SIZE(result, int);

    LinkedList<int> list(arr, size);
    list.PopBack();

    containersEqual(list, result, resultSize);
    EXPECT_EQ(list.GetSize(), resultSize);
}

TEST(LinkedList, PopFront1) {
    int arr[] = {4544, 798634, 78988, 454};
    int result[] = {798634, 78988, 454};

    int size = ARRAY_SIZE(arr, int);
    int resultSize = ARRAY_SIZE(result, int);

    LinkedList<int> list(arr, size);
    list.PopFront();

    containersEqual(list, result, resultSize);
    EXPECT_EQ(list.GetSize(), resultSize);
}

TEST(LinkedList, PopBack2) {
    int arr[] = {4544};

    LinkedList<int> list(arr, 1);
    list.PopBack();

    EXPECT_EQ(list.GetSize(), 0);
}

TEST(LinkedList, PopFront2) {
    int arr[] = {4544};

    LinkedList<int> list(arr, 1);
    list.PopFront();

    EXPECT_EQ(list.GetSize(), 0);
}

TEST(LinkedList, PopBack3) {
    LinkedList<int> list;
    list.PopBack();

    EXPECT_EQ(list.GetSize(), 0);
}

TEST(LinkedList, PopFront3) {
    LinkedList<int> list;
    list.PopFront();

    EXPECT_EQ(list.GetSize(), 0);
}

TEST(LinkedList, InsertLast)
{
    int arr[] = {4544, 798634, 78988, 454};
    int answer[] = {4544, 798634, 78988, 454, 10};

    LinkedList<int> list(arr, ARRAY_SIZE(arr, int));
    list.InsertAt(10, list.GetSize());

    containersEqual(answer, list, ARRAY_SIZE(answer, int));
    EXPECT_EQ(list.GetSize(), ARRAY_SIZE(answer, int));
}

TEST(LinkedList, InsertFirst)
{
    int arr[] = {4544, 798634, 78988, 454};
    int answer[] = {10, 4544, 798634, 78988, 454};

    LinkedList<int> list(arr, ARRAY_SIZE(arr, int));
    list.InsertAt(10, 0);

    containersEqual(answer, list, ARRAY_SIZE(answer, int));
    EXPECT_EQ(list.GetSize(), ARRAY_SIZE(answer, int));
}

TEST(LinkedList, Insert)
{
    int arr[] = {4544, 798634, 78988, 454};
    int answer[] = {4544, 798634, 11, 78988, 454};

    LinkedList<int> list(arr, ARRAY_SIZE(arr, int));
    list.InsertAt(10, 2);

    containersEqual(answer, list, ARRAY_SIZE(answer, int));
    EXPECT_EQ(list.GetSize(), ARRAY_SIZE(answer, int));
}

TEST(LinkedList, InsertZero)
{
    int answer[] = {10};

    LinkedList<int> list;
    list.InsertAt(10, 0);

    containersEqual(answer, list, ARRAY_SIZE(answer, int));
    EXPECT_EQ(list.GetSize(), ARRAY_SIZE(answer, int));
}
