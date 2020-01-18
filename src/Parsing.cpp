#include <cstring>
#include <iostream>
#include <array>
#include <string>
#include "Utility.hpp"
#include "Friend.hpp"

Friend::Parsing::Parsing(const std::string &fPath)
{
    _read.open(fPath.c_str());
    if (!_read) {
        std::cerr << "[ERROR] : File could not be opened" << std::endl;
        exit(84);
    }
}

void Friend::Parsing::checkErrors(void)
{
    std::string line;

    while (std::getline(_read, line)) {
        while (line.length() == 0
        || hasOnlySpacesTabs(line)) {
            if (!std::getline(_read, line)) {
                exit (84);
            }
        }
        if (line.find("is friends with") == std::string::npos)
            exit (84);
    }
    _read.clear();
    _read.seekg(0, std::ios::beg);
}

void Friend::Parsing::makeList(MAP_PEOPLE &people, SET_FRIENDSHIP &friendship)
{
    std::array<std::pair<std::string, char[256]>, 2> tmpPeople;

    while (_read >> tmpPeople[0].first) {
        if (tmpPeople[0].first != "is" && tmpPeople[0].first != "friends"
        && tmpPeople[0].first != "with") {
            _read >> tmpPeople[0].second;
            tmpPeople[0].first += strcmp(tmpPeople[0].second, "is") != 0 ? " "
            + static_cast<std::string>(tmpPeople[0].second) : "\0";
            people.insert({tmpPeople[0].first, 0});
            tmpPeople[1].first.assign(tmpPeople[0].first);
        }
        if (tmpPeople[0].first == "with") {
            _read.ignore();
            _read.get(&tmpPeople[0].second[0], 256, '\n');
            people.insert({tmpPeople[0].second, 0});
            strcpy(tmpPeople[1].second, tmpPeople[0].second);
            friendship.emplace(tmpPeople[1].first, tmpPeople[1].second);
            _read.ignore();
        }
    }
}

Friend::Parsing::~Parsing()
{
    _read.close();
}
