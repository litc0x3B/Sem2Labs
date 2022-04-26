#pragma once

#include <gtest/gtest.h>

#define ARRAY_SIZE(array, type) sizeof(array) / sizeof(type)

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
      std::cerr << "Expected equality of these values:" << std::endl;
      std::cerr << "\t{";
      for (int i = 0; i < size; i++)
      {
         std::cerr << container1[i];
         if (i != size - 1)
         {
            std::cerr << ", ";
         }
      }
      std::cerr << "}" << std::endl << "\t{";

      for (int i = 0; i < size; i++)
      {
         std::cerr << container2[i];
         if (i != size - 1)
         {
            std::cerr << ", ";
         }
      }
      std::cerr << "}" << std::endl;
      FAIL();
   }

}
