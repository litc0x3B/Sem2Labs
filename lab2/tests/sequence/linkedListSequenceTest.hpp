#include "TestHelper.hpp"
#include "sequence/linkedListSequence.hpp"
#include "sequence/sequence.hpp"

TEST(linkedListSequenceTest, constructorFromArr)
{
    Sequence<int> *list = new LinkedListSequence<int>(testArr, testArrSize);

    containersEqual(*list, testArr, testArrSize);
    EXPECT_EQ(testArrSize, list->GetSize());

    delete list;
}

TEST(linkedListSequenceTest, constructorEmpty)
{
    Sequence<int> *list = new LinkedListSequence<int>();
    delete list;
}

TEST(linkedListSequenceTest, constructorCopy)
{
    Sequence<int> *list1 = new LinkedListSequence<int>(testArr, testArrSize);
    Sequence<int> *list2 = new LinkedListSequence<int>(*(LinkedListSequence<int>*)list1);

    containersEqual(*list1, *list2, testArrSize);
    EXPECT_EQ(list1->GetSize(), list2->GetSize());

    delete list1;
    delete list2;
}

TEST(linkedListSequenceTest, append)
{
    Sequence<int> *list = new LinkedListSequence<int>(testArr, testArrSize);
    int answer[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    list->Append(8);

    containersEqual(*list, answer, testArrSize + 1);
    EXPECT_EQ(list->GetSize(), testArrSize + 1);

    delete list;
}

TEST(linkedListSequenceTest, prepend)
{
    Sequence<int> *list = new LinkedListSequence<int>(testArr, testArrSize);
    int answer[] = {-1, 0, 1, 2, 3, 4, 5, 6, 7};

    list->Prepend(-1);

    containersEqual(*list, answer, testArrSize + 1);
    EXPECT_EQ(list->GetSize(), testArrSize + 1);

    delete list;
}

TEST(linkedListSequenceTest, insertAt)
{
    Sequence<int> *list = new LinkedListSequence<int>(testArr, testArrSize);
    int answer[] = {0, 1, 2, 100, 3, 4, 5, 6, 7};

    list->InsertAt(100, 3);

    containersEqual(*list, answer, testArrSize + 1);
    EXPECT_EQ(list->GetSize(), testArrSize + 1);

    delete list;
}

TEST(linkedListSequenceTest, concat)
{
    int arr1[] = {0, 1, 2};
    int arr2[] = {3, 4, 5, 6, 7};
    
    Sequence<int> *list1 = new LinkedListSequence<int>(arr1, ARRAY_SIZE(arr1, int));
    Sequence<int> *list2 = new LinkedListSequence<int>(arr2, ARRAY_SIZE(arr2, int));
    Sequence<int> *list = list1->Concat(list2);

    containersEqual(*list, testArr, testArrSize);
    EXPECT_EQ(list->GetSize(), testArrSize);

    delete list1;
    delete list2;
    delete list;
}

TEST(linkedListSequenceTest, subsequence)
{
    int answer[] = {3, 4, 5, 6};
    Sequence<int> *list = new LinkedListSequence<int>(testArr, testArrSize);
    Sequence<int> *subList = list->GetSubsequence(3, 6);

    containersEqual(*subList, answer, ARRAY_SIZE(answer, int));
    EXPECT_EQ(subList->GetSize(), ARRAY_SIZE(answer, int));
    
    delete list;
    delete subList;
}

TEST(linkedListSequenceTest, popback)
{
    int answer[] = {0, 1, 2, 3, 4, 5, 6};
    Sequence<int> *list = new LinkedListSequence<int>(testArr, testArrSize);
    list->PopBack();

    containersEqual(*list, answer, ARRAY_SIZE(answer, int));
    EXPECT_EQ(list->GetSize(), ARRAY_SIZE(answer, int));
    
    delete list;
}

TEST(linkedListSequenceTest, popfront)
{
    int answer[] = {1, 2, 3, 4, 5, 6, 7};
    Sequence<int> *list = new LinkedListSequence<int>(testArr, testArrSize);
    list->PopFront();

    containersEqual(*list, answer, ARRAY_SIZE(answer, int));
    EXPECT_EQ(list->GetSize(), ARRAY_SIZE(answer, int));
    
    delete list;
}

TEST(linkedListSequenceTest, delete)
{
    int answer[] = {0, 1, 3, 4, 5, 6, 7};
    Sequence<int> *list = new LinkedListSequence<int>(testArr, testArrSize);
    list->Delete(2);

    containersEqual(*list, answer, ARRAY_SIZE(answer, int));
    EXPECT_EQ(list->GetSize(), ARRAY_SIZE(answer, int));
    delete list;
}