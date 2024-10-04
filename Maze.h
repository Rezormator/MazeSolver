#pragma once

#include <vector>
#include <random>
#include "Point.h"

enum Cell {
    WALL, PATH, WAY, START, FINISH
};

typedef std::vector<std::vector<Cell> > maze;
typedef std::default_random_engine dre;

class Maze {
private:
    static bool isValidMove(Point point, const maze &maze);
    static void generateMaze(maze &maze, Point startPoint, dre &rng);
public:
    static maze createStartMaze(int size, Point startPoint);
    static void printMaze(maze& maze, const Point& start = Point(1, 1),
        const Point& finish = Point(0, 0), bool showFinish = false);
};
