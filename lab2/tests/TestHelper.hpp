#pragma once

#include <gtest/gtest.h>

#define ARRAY_SIZE(array, type) sizeof(array) / sizeof(type)

const int testArr[] = {0, 1, 2, 3, 4, 5, 6, 7};
const int testArrSize = ARRAY_SIZE(testArr, int);

template <typename T>
std::stringstream containerToStream(T &container, int size)
{
    std::stringstream stream;
    stream << "{";
    for (int i = 0; i < size; i++)
    {
        stream << container[i];
        if (i != size - 1)
        {
            stream << ", ";
        }
    }
    stream << "}";

    return stream;
}

template <typename T1, typename T2>
void containersEqual(T1 &container1, T2 &container2, int size)
{
   bool areEqual = true;

   for (int i = 0; i < size; i++)
   {
      areEqual = container1[i] == container2[i];
      if (!areEqual)
      {
         break;
      }
   }

   if (!areEqual)
   {
       std::stringstream errorStream;
       errorStream << "Expected equality of these values:" << std::endl;
       errorStream << "\t" << containerToStream(container1, size).rdbuf() << std::endl;
       errorStream << "\t" << containerToStream(container2, size).rdbuf() << std::endl;
       FAIL() << errorStream.rdbuf();
   }
}

template<typename T>
void showContainer(T &container, int size)
{
    std::cout << containerToStream(container, size).rdbuf() << std::endl;
}
