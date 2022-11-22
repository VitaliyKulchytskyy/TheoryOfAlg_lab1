#ifndef LAB1_MAZE_H
#define LAB1_MAZE_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<size_t, size_t>    point_t;
typedef vector<point_t>         trail_t;
[[maybe_unused]]
typedef vector<trail_t>         graph_t;

class Maze final {
private:
    string *m_asMap;
    const size_t m_iRowAmount;
    const size_t m_iColumnAmount;
private:
    point_t findCharPointInMap(char) const;
public:
    Maze() = delete;
    Maze(string *, size_t, size_t);
public:
    char& operator[] (point_t);
    void printMaze() const;
public:
    [[nodiscard]]
    trail_t getNeighborhoods(point_t) const;
    point_t getStartPoint() const;
    point_t getFinishPoint() const;
    size_t getRowAmount() const;
    size_t getColumnAmount() const;
public:
    bool isValid(size_t, size_t) const;
    bool isValid(point_t) const;
    bool isStartOrFinishPoint(point_t) const;
    bool isNeighborhood(point_t, point_t) const;
};

#endif
