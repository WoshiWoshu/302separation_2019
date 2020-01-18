#pragma once

#include <fstream>
#include <map>
#include <set>

using MAP_PEOPLE = std::map<std::string, std::size_t>;
using SET_FRIENDSHIP = std::set<std::pair<std::string, std::string>>;

class Friend {

private:
    class Parsing {
    public:
        inline Parsing() : _read(0) {};
        explicit Parsing(const std::string &fPath);
        ~Parsing();
        void makeList(MAP_PEOPLE &people, SET_FRIENDSHIP &friendship);
        void checkErrors(void);
    private:
        std::ifstream _read;
    };

public:
    Friend() = default;
    inline explicit Friend(const std::string &file) : _parsing(file) {}
    ~Friend() = default;
    inline MAP_PEOPLE getPeople(void) const { return _people; }
    inline SET_FRIENDSHIP getFriendship(void) const { return _friendship; }
    void generateList(void);
    void displayList(void) const;
protected:
    MAP_PEOPLE _people;
    SET_FRIENDSHIP _friendship;
    Parsing _parsing;
private:
    void assignPeopleValue(void);
};
