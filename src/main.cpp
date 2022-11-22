#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include "Queue.h"
#include "Maze.h"
#include "MyTest.h"
#include "../test/test.h"

#define DEBUG_MODE          0
#define TEST_QUEUE          1
#define PRINT_STEP_BY_STEP  1

using namespace std;

struct Distance {
    size_t dist = 0;
    point_t vertex = {0, 0};

    Distance() = default;
    Distance(size_t _dist, point_t _vertex)
        : dist{_dist}, vertex{std::move(_vertex)}
    {}
};

void buildBacktrackingTrail(Maze &maze, vector<Distance> trail) {
    Distance curr = trail[trail.size() - 1];
    size_t iPrevDistance = curr.dist;

    #if PRINT_STEP_BY_STEP == true
        uint16_t stepCounter = 1;
        cout << "[START STEP BY STEP DEBUG]\n\n";
    #endif

    for(auto it = trail.cend(); it != trail.cbegin(); it--) {
        if(iPrevDistance == it->dist + 1 &&
           maze.isNeighborhood(it->vertex, curr.vertex))
        {
            if(!maze.isStartOrFinishPoint(curr.vertex)) {
                maze[curr.vertex] = '*';
                #if PRINT_STEP_BY_STEP == true
                    cout << "[STEP: " << stepCounter++ << "/" << trail[trail.size() - 1].dist - 1 << "]\n";
                    maze.printMaze();
                    cout << '\n';
                #endif
            }
            curr = *it;
            iPrevDistance = curr.dist;
        }
    }

    #if PRINT_STEP_BY_STEP == true
        cout << "[END STEP BY STEP DEBUG]\n\n";
    #endif
}

void bfs(Maze &maze) {
    const auto& startPoint = maze.getStartPoint();
    map<point_t, bool> visited;
    visited[startPoint] = true;

    Queue<Distance> q;
    q.add(Distance(0, startPoint));

    vector<Distance> distanceFromStart;
    distanceFromStart.push_back(Distance(0, startPoint));

    const auto& finishPoint = maze.getFinishPoint();
    while(q.size() != 0) {
        const Distance curr = q.front();

        if(curr.vertex == finishPoint) {
            distanceFromStart.push_back(Distance(curr.dist, finishPoint));
            #if DEBUG_MODE == true
                maze[curr.vertex] = (char)curr.dist + '0';
            #endif
            buildBacktrackingTrail(maze, distanceFromStart);
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
                distanceFromStart.push_back(curr);
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