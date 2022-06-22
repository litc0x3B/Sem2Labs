#include "lab3UI/lab3UI.hpp"
#include "lab3UI/myDequeUI.hpp"
#include "lab3UI/mySetUI.hpp"
#include "lab3UI/myStackOrQueueUI.hpp"

int main()
{
    lab3UI::ContainerInfo containerInfo;

    containerInfo.containerType = (lab3UI::ContainerType)lab3UI::select
    (
        "Выберете тип контейнера", 
        "1) Стек", 
        "2) Множество",
        "3) Дек",
        "4) Очередь"
    );

    containerInfo.dataType = (lab3UI::DataType)lab3UI::select
    (
        "Выберете тип данных: ", 
        "1) Person", 
        "2) float"
    );

    containerInfo.sequenceType = (lab3UI::SequenceType)lab3UI::select
    (
        "Выберете тип используемой последовательности: ", 
        "1) DynamicArraySequence",
        "2) LinkedListSequence"
    );

    int autoInput = (lab3UI::SequenceType)lab3UI::select
    (
        "Хотите включить автоввод: ", 
        "1) Да",
        "2) Нет"
    );

    if(autoInput == 1)
    {
        lab3UI::autoInput = true;
    }
    else 
    {
        lab3UI::autoInput = false;
    }

    if (containerInfo.containerType == lab3UI::ContainerType::set)
    {
        MySetUI::initMenu(containerInfo);
    }
    else if (containerInfo.containerType == lab3UI::ContainerType::stack || containerInfo.containerType == lab3UI::ContainerType::queue)
    {
        myStackOrQueueUI::initMenu(containerInfo);
    }
    else if (containerInfo.containerType == lab3UI::ContainerType::deque)
    {
        MyDequeUI::initMenu(containerInfo);
    }

    return 0;
}

