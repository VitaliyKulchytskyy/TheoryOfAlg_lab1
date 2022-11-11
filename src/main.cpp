#include <iostream>
#include <cstring>
#include <map>
#include <utility>
#include <vector>
#include "Queue.h"
#include "Maze.h"
#include "MyTest.h"
#include "../test/test.h"

#define DEBUG_MODE  0
#define TEST_QUEUE  1

using namespace std;

struct Distance {
    size_t dist = 0;
    point_t vertex = {0, 0};

    Distance(size_t _dist, point_t _vertex)
        : dist{_dist}, vertex{std::move(_vertex)}
    {}

    Distance() = default;
};

void buildBacktrackingTrail(Maze &maze, vector<Distance> trail) {
    Distance curr = trail[trail.size() - 1];
    size_t iPrevDistance = curr.dist;
    for(auto it = trail.cend(); it != trail.cbegin(); it--) {
        if(iPrevDistance == it->dist + 1 &&
           maze.isNeighborhood(it->vertex, curr.vertex))
        {
            if(!maze.isStartOrFinishPoint(curr.vertex))
                maze[curr.vertex] = '*';
            curr = *it;
            iPrevDistance = curr.dist;
        }
    }
}

void bfs(Maze &maze) {
    const auto& startPoint = maze.getStartPoint();
    map<point_t, bool> visited;
    visited[startPoint] = true;

    Queue<Distance> q;
    q.add(Distance(0, startPoint));


    vector<Distance> weightedGraph;
    weightedGraph.push_back(Distance(0, startPoint));

    const auto& finishPoint = maze.getFinishPoint();
    while(q.size() != 0) {
        const Distance curr = q.front();

        if(curr.vertex == finishPoint) {
            weightedGraph.push_back(Distance(curr.dist, finishPoint));
            #if DEBUG_MODE == true
                maze[curr.vertex] = (char)curr.dist + '0';
            #endif
            buildBacktrackingTrail(maze, weightedGraph);
            return;
        }
        q.poll();

        const auto& neighborhoods = maze.getNeighborhoods(curr.vertex);
        for(const auto& vertex : neighborhoods) {
            if(!visited[vertex] && maze.isValid(vertex)) {
                visited[curr.vertex] = true;
                q.add(Distance(curr.dist + 1, vertex));
            }
            #if DEBUG_MODE == false
                weightedGraph.push_back(curr);
            #else
                maze[curr.vertex] = (char)curr.dist + '0';
            #endif
        }
    }
    cout << "[!] There is no way to escape from the maze.\n";
}

int main() {
    #if TEST_QUEUE == 1
        Test::doTest();
        cout << '\n';
    #endif

    string map[] = {
            {"#-S-----"},
            {"##-#-###"},
            {"--------"},
            {"-####-#-"},
            {"-----#--"},
            {"--#-F#--"},
            {"--####--"},
            {"#-------"}
    };

    Maze maze = Maze(map, sizeof(map)/sizeof(string), map[0].length());
    bfs(maze);
    maze.printMaze();

    return 0;
}