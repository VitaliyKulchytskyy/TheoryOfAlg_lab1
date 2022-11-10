#include "Maze.h"

//-----[PUBLIC]-----
Maze::Maze(string *map, size_t row, size_t column)
    : m_asMap{map},
      m_iRowAmount{row},
      m_iColumnAmount{column}
{}

char& Maze::operator[](point_t index) {
    if(isValid(index))
        return m_asMap[index.first][index.second];
}

void Maze::printMaze() const {
    for(size_t i = 0; i < m_iRowAmount; i++) {
        for(size_t j = 0; j < m_iColumnAmount; j++)
            cout << m_asMap[i][j];
        cout << '\n';
    }
}

trail_t Maze::getNeighborhoods(point_t getFrom) const {
    trail_t output;

    const int16_t directions[4][2] = {
            {0, 1},
            {0, -1},
            {1, 0},
            {-1, 0}
    };

    for(const auto& direction : directions) {
        point_t next = {getFrom.first + direction[0],
                        getFrom.second + direction[1]};
        if(isValid(getFrom) && isValid(next))
            output.push_back(next);
    }

    return output;
}

point_t Maze::getStartPoint() const {
    return findCharPointInMap('S');
}

point_t Maze::getFinishPoint() const {
    return findCharPointInMap('F');
}

size_t Maze::getRowAmount() const {
    return m_iRowAmount;
}

size_t Maze::getColumnAmount() const {
    return m_iColumnAmount;
}

bool Maze::isValid(size_t row, size_t column) const {
    if(row < m_iRowAmount && column < m_iColumnAmount)
        return m_asMap[row][column] != '#';
    return false;
}

bool Maze::isValid(point_t checkPair) const {
    return isValid(checkPair.first, checkPair.second);
}

bool Maze::isStartOrFinishPoint(point_t checkPair) const {
    return checkPair == getStartPoint() ||
           checkPair == getFinishPoint();
}

bool Maze::isNeighborhood(point_t pointA, point_t pointB) const {
    const auto& pointANeighborhoods = getNeighborhoods(pointA);
    return any_of(pointANeighborhoods.cbegin(),
                  pointANeighborhoods.cend(),
                  [&pointB](point_t input){ return input == pointB; });
}

//-----[PRIVATE]-----
point_t Maze::findCharPointInMap(char findChar) const {
    for(size_t i = 0; i < getRowAmount(); i++)
        for(size_t j = 0; j < getColumnAmount(); j++)
            if(m_asMap[i][j] == findChar)
                return {i, j};
}
