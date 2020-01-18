#include <vector>
#include "Friend.hpp"

static const bool ADJACENCY = 0;
static const bool SHORTEST_PATHS = 1;

class Matrix : public Friend {

    using VECTOR_2D = std::vector<std::vector<std::size_t>>;
    using VECTOR_3D = std::vector<std::vector<std::vector<std::size_t>>>;

public:
    inline explicit Matrix(const std::size_t &n)
    : _n(n), _adjacency(0) {}
    ~Matrix() = default;
    Matrix &operator=(const Friend &friendCopy);
    void buildAdjacency(void);
    void buildShortestPaths(void);
    void showDegreeOfSeparation(const std::string &personA,
    const std::string &personB);
    void displayMatrix(const bool &matrixType) const;
    const std::size_t _n;
private:
    VECTOR_2D _adjacency;
    VECTOR_3D _shortestPaths;
    void sumMatrix(void);
};
