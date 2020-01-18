#include <iostream>
#include <iterator>
#include "Friend.hpp"

void Friend::displayList(void) const
{
    for (auto i : _people)
        std::cout << i.first << std::endl;
}

void Friend::assignPeopleValue(void)
{
    int value = 0;
    for (auto &i : _people)
        i.second = value++;
}

void Friend::generateList(void)
{
    _parsing.checkErrors();
    _parsing.makeList(_people, _friendship);
    if (_people.size() == 0)
        exit(84);
    this->assignPeopleValue();
}
