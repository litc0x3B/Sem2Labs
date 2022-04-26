cmake_minimum_required(VERSION 3.0)

project(lab2)

# Locate GTest
find_package(GTest REQUIRED)

include_directories(include tests ${GTEST_INCLUDE_DIRS})
add_executable(tests
    src/tests.cpp
    include/dynamicArray.hpp
    include/linkedList.hpp
    tests/linkedListTest.hpp
    tests/TestHelper.hpp)

target_link_libraries(tests ${GTEST_LIBRARIES} pthread)

install(TARGETS tests RUNTIME DESTINATION bin)

