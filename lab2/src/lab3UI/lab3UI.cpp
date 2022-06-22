#include <chrono>
#include <iostream>
#include <math.h>
#include <string>

#include "lab3UI/lab3UI.hpp"

bool Person::operator==(Person &person) const
{
    return (id == person.id && name == person.name);
}

bool Person::operator!=(Person &person) const
{
    return !(*this == person);
}

bool Person::operator>(Person &person) const
{
    return this->name > person.name;
}


Person Person::operator+=(const int num)
{
    id += num;
    return (*this);
}


bool lab3UI::autoInput = false;

void lab3UI::printStarString()
{
    int stringLen = 10;
    for (int i = 0; i < stringLen; i++)
    {
        std::cout << '*';
    }
    std::cout << std::endl;
}

std::chrono::time_point<std::chrono::steady_clock> lab3UI::getNow()
{
    return std::chrono::steady_clock::now();
}

void lab3UI::elapsedTimeOutput(std::chrono::time_point<std::chrono::steady_clock, std::chrono::nanoseconds> const& start)
{
    auto delta = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start);
    printStarString();
    std::cout << "Затарченное время(µs): " << delta.count() << std::endl;
}


void lab3UI::output(float num)
{
    std::cout << "Число: " << num << std::endl;
}

void lab3UI::output(Person person)
{
    std::cout << "ID: " << person.id << " ";
    std::cout << "Имя: " << person.name << std::endl;
}

template<class T>
T lab3UI::input()
{   
    T value;

    static const int maxSignificand = 1000;
    static const int exponent = -1;

    if (autoInput)
    {   
        value = float(std::rand() % (maxSignificand + 1)) * powf(10, exponent);
        value *= std::rand() <= RAND_MAX / 2 ? 1 : -1;
        output(value);
    }
    else
    {
        std::cout << "Введите значение: ";
        std::cin >> value;
    }

    return value;
}

template<>
Person lab3UI::input<Person>()
{   
    Person person;

    static const std::string names[] = {"Oliver","George","Arthur","Noah","Muhammad","Leo","Oscar","Harry","Archie","Jack","Henry",
        "Charlie","Freddie","Theodore","Thomas","Finley","Theo","Alfie","Jacob","William","Isaac","Tommy","Joshua","James","Lucas",
        "Alexander","Arlo","Roman","Edward","Elijah","Teddy","Mohammed","Max","Adam","Albie","Ethan","Logan","Joseph","Sebastian",
        "Benjamin","Harrison","Mason","Rory","Reuben","Luca","Louie","Samuel","Reggie","Jaxon","Daniel","Hugo","Louis","Jude","Ronnie",
        "Dylan","Zachary","Albert","Hunter","Ezra","David","Frankie","Toby","Frederick","Carter","Gabriel","Grayson","Riley","Jesse",
        "Hudson","Bobby","Rowan","Jenson","Finn","Michael","Mohammad","Stanley","Felix","Jasper","Liam","Milo","Sonny","Oakley","Elliot",
        "Chester","Caleb","Harvey","Elliott","Charles","Ellis","Jackson","Alfred","Ollie","Leon","Yusuf","Ralph","Otis","Harley","Ibrahim",
        "Jayden","Myles"};
    
    static const int namesSize = sizeof(names) / sizeof(std::string);
    static const int maxId = 100;

    if (autoInput)
    {
        person.name = names[rand() % namesSize];
        person.id = rand() % (maxId + 1);
        output(person);
    }
    else 
    {
        std::cout << "Введите ID: ";
        std::cin >> person.id;
        std::cout << "Введите имя: ";
        std::cin >> person.name;
    }

    return person;
}

template float lab3UI::input<float>();
