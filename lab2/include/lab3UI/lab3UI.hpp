#pragma once

#include <string>
#include <chrono>
#include <iostream>

class Person
{
public:
    unsigned int id = 0;
    std::string name = "";

    bool operator==(Person &person) const;
    bool operator!=(Person &person) const;
    bool operator>(Person &person) const;
    bool operator<(Person &person) const;
    Person operator+=(const int num);
};

namespace lab3UI
{
    enum ContainerType
    {
        stack = 1,
        set = 2,
        deque = 3,
        queue = 4
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

    template<typename... Args>
    int select(std::string message, Args... optionStrings)
    {
        bool success = false;
        int ret;

        do 
        {
            std::cout << message << std::endl;
            for (std::string str : {optionStrings...})
            {
                std::cout << str << std::endl;
            }

            std::cin >> ret;

            if (ret <= sizeof...(Args) && ret >= 1)
            {
                success = true;
            }
            else 
            {
                std::cout << "Неизвестная команда" << std::endl;
            }

        } while(!success);

        return ret;
    }

    extern bool autoInput;

    std::chrono::time_point<std::chrono::steady_clock> getNow();
    void elapsedTimeOutput(std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds> const& start);

    void printStarString();
    void output(float num);
    void output(Person person);

    template<class T> T input();
    template<> Person input<Person>();
    
};
