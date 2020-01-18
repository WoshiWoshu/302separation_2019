#include <iostream>
#include <cmath>
#include "Matrix.hpp"

Matrix &Matrix::operator=(const Friend &friendCpy)
{
    if (this != &friendCpy) {
        _people = friendCpy.getPeople();
        _friendship = friendCpy.getFriendship();
    }
    return *this;
}

void Matrix::displayMatrix(const bool &matrixType) const
{
    VECTOR_2D matrix(0);

    std::cout << std::endl;
    if (matrixType == SHORTEST_PATHS)
        matrix = _shortestPaths.at(_n - 1);
    if (matrixType == ADJACENCY)
        matrix = _adjacency;
    for (std::size_t i = 0; i < matrix.size(); i++) {
        for (std::size_t j = 0; j < matrix.at(i).size(); j++) {
            std::cout << matrix.at(i).at(j);
            if (j < matrix.at(i).size() - 1)
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::sumMatrix(void)
{
    std::size_t ll(0);

    const std::size_t size = _people.size();
    for (std::size_t i = 0; i < size; i++) {
        for (std::size_t j = 0; j < size; j++) {
            if(i != j) {
                ll = 0;
                while (ll < _n && _shortestPaths[ll][i][j] == 0)
                    ll += 1;
                if (ll < _n - 1)
                    _shortestPaths[_n - 1][i][j] = ll + 1;
                else if (_shortestPaths[_n - 1][i][j] > 0)
                    _shortestPaths[_n - 1][i][j] = _n;
            } else
                _shortestPaths[_n - 1][i][j]=0;
        }
    }
}

void Matrix::showDegreeOfSeparation(const std::string &personA,
    const std::string &personB)
{
    if (_people.find(personA) == _people.end()
    || _people.find(personB) == _people.end()) {
        std::cout << "Degree of separation between " << personA << " and "
        << personB << ": -1" << std::endl;
    }
    else {
        std::cout << "Degree of separation between " << personA << " and "
        << personB << ": " <<
        _shortestPaths[_n - 1][_people[personA]][_people[personB]] << std::endl;
    }
}

void Matrix::buildShortestPaths(void)
{
    const std::size_t size = _people.size();

    for (std::size_t l = 0; l < _n; l++) {
        if (l == 0) {
            _shortestPaths.push_back(_adjacency);
            continue;
        }
        _shortestPaths.push_back(VECTOR_2D(size, std::vector<size_t>(size, 0)));
        for (std::size_t i = 0; i < size; i++) {
            for (std::size_t j = 0; j < size; j++) {
                for (std::size_t k = 0; k < size; k++) {
                    if (l == 1) {
                        _shortestPaths[l][i][j]
                        += _adjacency[i][k] * _adjacency[k][j];
                    } else {
                        _shortestPaths[l][i][j] += _shortestPaths[l - 1][i][k]
                        * _adjacency[k][j];
                    }
                }
            }
        }
    }
    this->sumMatrix();
}

void Matrix::buildAdjacency(void)
{
    const std::size_t size = _people.size();

    for (std::size_t i = 0; i < size; i++)
        _adjacency.push_back(std::vector<size_t>(size, 0));
    for (SET_FRIENDSHIP::iterator itSet = _friendship.begin();
    itSet != _friendship.end(); itSet++) {
        _adjacency[_people[itSet->first]][_people[itSet->second]] = 1;
        _adjacency[_people[itSet->second]][_people[itSet->first]] = 1;
    }
}
