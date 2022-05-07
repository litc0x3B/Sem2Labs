cmake_minimum_required(VERSION 3.0)

project(lab2)

# Locate GTest
find_package(GTest REQUIRED)

include_directories(include tests ${GTEST_INCLUDE_DIRS})
add_executable(tests
        src/tests.cpp
        include/dynamicArray.hpp
        include/linkedList.hpp
        include/myStack.hpp
        include/mySet.hpp
        include/sequence/linkedListSequence.hpp
        include/sequence/sequence.hpp
        include/sequence/dynamicArraySequence.hpp
        tests/TestHelper.hpp
        tests/linkedListTest.hpp
        tests/myStackTest.hpp
        tests/mySetTest.hpp
        tests/sequence/linkedListSequenceTest.hpp
        tests/sequence/dynamicArraySequenceTest.hpp)

add_executable(lab2UI
        src/lab2UI.cpp
        include/dynamicArray.hpp
        include/linkedList.hpp
        include/sequence/sequence.hpp
        include/sequence/linkedListSequence.hpp
        include/sequence/dynamicArraySequence.hpp)

target_link_libraries(tests ${GTEST_LIBRARIES} pthread)

target_compile_features(tests PRIVATE cxx_std_17)
target_compile_features(lab2UI PRIVATE cxx_std_17)


install(TARGETS tests RUNTIME DESTINATION bin)
install(TARGETS lab2UI RUNTIME DESTINATION bin)

