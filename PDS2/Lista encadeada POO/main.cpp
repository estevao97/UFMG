#include "List.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    int input;
    std::cin >> input;
    List *list = new List();
    while (input != 0)
    {
        list->insert(input);
        std::cin >> input;
    }
    std::cout << "s:" << list->size() << ", ";
    std::cout << "m:" << list->middle() << ", ";
    std::cout << "l:" << list->last() << ", ";
    std::cout << "r:" << list->remove() << ", ";
    std::cout << "m:" << list->middle() << ", ";
    std::cout << "l:" << list->last() << ", ";
    list->rotate();
    std::cout << "m:" << list->middle() << ", ";
    std::cout << "l:" << list->last() << std::endl;
    while (list->isEmpty())
    {
        list->remove();
    }
    return 0;
}
