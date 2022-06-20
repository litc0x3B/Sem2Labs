cmake_minimum_required(VERSION 3.0.0)
project(lab3 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(
    tests 
    binTree.hpp
    set.hpp
    priorityQueue.hpp
    icollection.hpp 
    test.cpp 
    test_binTree.hpp
    test_set.hpp
)

add_executable(
    main
    main.cpp
    binTree.hpp
    set.hpp
    priorityQueue.hpp
    icollection.hpp 
)

target_link_libraries(
  tests
  gtest_main
)

include(GoogleTest)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})