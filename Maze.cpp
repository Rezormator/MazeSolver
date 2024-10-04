#include "Maze.h"
#include <algorithm>
#include <iostream>

maze Maze::createStartMaze(const int size, const Point startPoint) {
    std::vector<std::vector<Cell>> maze(size, std::vector<Cell>(size, WALL));
    maze[startPoint.y][startPoint.x] = PATH;

    std::random_device rd;
    std::default_random_engine rng(rd());
    generateMaze(maze, startPoint, rng);

    return maze;
}

void Maze::generateMaze(maze& maze, const Point startPoint, dre& rng) {
    std::vector<Point> directions = {{2, 0}, {0, 2}, {-2, 0}, {0, -2}};
    std::ranges::shuffle(directions, rng);

    for (const auto& [dx, dy] : directions) {
        const Point newPoint(startPoint.x + dx, startPoint.y + dy);

        if (!isValidMove(newPoint, maze))
            continue;

        maze[newPoint.y][newPoint.x] = PATH;
        maze[startPoint.y + dy / 2][startPoint.x + dx / 2] = PATH;
        // printMaze(maze);
        generateMaze(maze, newPoint, rng);
    }
}

bool Maze::isValidMove(const Point point, const maze& maze) {
    if (point.x <= 0 || point.x >= maze.size() - 1 || point.y <= 0 || point.y >= maze.size() - 1)
        return false;
    return maze[point.y][point.x] == WALL;
}

void Maze::printMaze(maze& maze, const Point& start, const Point& finish, const bool showFinish) {
    maze[start.y][start.x] = START;
    const auto finishCell = maze[finish.y][finish.x];
    if (showFinish)
        maze[finish.y][finish.x] = FINISH;

    std::cout << "Wall: [\033[47m  \033[0m], Path: [  ], Start: [\033[41m  \033[0m],"
                 " Finish: [\033[42m  \033[0m], Way: [\033[44m  \033[0m]\n" << std::endl;

    for (const auto &row : maze) {
        for (const auto& cell : row)
            switch (cell) {
                case WALL:
                    std::cout << "\033[47m  \033[0m";
                break;
                case WAY:
                    std::cout << "\033[44m  \033[0m";
                break;
                case START:
                    std::cout << "\033[41m  \033[0m";
                break;
                case FINISH:
                    std::cout << "\033[42m  \033[0m";
                break;
                case PATH:
                    default:
                        std::cout << "  ";
                break;
            }
        std::cout << '\n';
    }
    std::cout << '\n';

    maze[start.y][start.x] = PATH;
    maze[finish.y][finish.x] = finishCell;
}
