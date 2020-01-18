#include <string>
#include <iostream>
#include <cstring>
#include "Utility.hpp"
#include "Matrix.hpp"

static void displayHelp(void)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./302separation file [n | p1 p2]" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tfile\tfile that contains the list of Facebook connections"
    << std::endl;
    std::cout << "\tn\tmaximum length of the paths" << std::endl;
    std::cout << "\tpi\tname of someone in the file" << std::endl;
}

void separation(const std::string &file, const std::size_t &n,
    const std::string &personA = "", const std::string &personB = "")
{
    Friend friends(file);
    Matrix matrix(n);

    friends.generateList();
    matrix = friends;
    matrix.buildAdjacency();
    matrix.buildShortestPaths();
    if (!personA.empty()) {
        matrix.showDegreeOfSeparation(personA, personB);
    } else {
        friends.displayList();
        matrix.displayMatrix(ADJACENCY);
        matrix.displayMatrix(SHORTEST_PATHS);
    }
}

int main(int ac, char **av)
{
    if (ac == 2 and strcmp(av[1], "-h") == 0)
        displayHelp();
    if (ac == 3) {
        if (std::atof(av[2]) == 0 || !isPosNum(av[2]))
            return 84;
        separation(av[1], std::atof(av[2]));
    }
    else if (ac == 4)
        separation(av[1], 6, av[2], av[3]);
    else
        return 84;
    return 0;
}
