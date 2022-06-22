#pragma once

#include <string>
#include <chrono>

class Person
{
public:
    unsigned int id = 0;
    std::string name = "";

    bool operator==(Person &person) const;
    bool operator!=(Person &person) const;
    bool operator>(Person &person) const;
    Person operator+=(const int num);
};

namespace lab3UI
{
    enum ContainerType
    {
        stack = 1,
        set = 2,
        deque = 3
    };

    enum DataType
    {
        personType = 1,
        floatType = 2,
    };

    enum SequenceType
    {
        array = 1,
        list = 2,
    };

    struct ContainerInfo
    {
        ContainerType containerType;
        DataType dataType;
        SequenceType sequenceType;
    };

    extern bool autoInput;

    std::chrono::time_point<std::chrono::steady_clock> getNow();
    void elapsedTimeOutput(std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds> const& start);

    void printStarString();
    void output(float num);
    void output(Person person);

    int select(std::string message, std::string option1, std::string option2, std::string option3 = "");
    template<class T> T input();
    template<> Person input<Person>();
    
};
