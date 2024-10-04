#include <iostream>
#include <vector>
#include <random>
#include "Maze.h"
#include "Node.h"
#include "Algorithms.h"

constexpr Point START_POINT = {13, 3};
constexpr Point FINISH_POINT = {75, 53};
constexpr int MAZE_SIZE = 99;

int main() {
    getchar();
    std::random_device rd;
    std::default_random_engine rng(rd());
    auto maze = Maze::createStartMaze(MAZE_SIZE, START_POINT);
    Maze::generateMaze(maze, START_POINT, rng);
    Maze::printMaze(maze, START_POINT, FINISH_POINT);
    getchar();

    std::vector nodes(MAZE_SIZE, std::vector<Node *>(MAZE_SIZE, nullptr));
    const auto root = Algorithms::mazeToTree(Node(START_POINT), maze, nodes);

    // std::vector<std::vector<bool>> visited(MAZE_SIZE, std::vector<bool>(MAZE_SIZE, false));
    // root->printTree(MAZE_SIZE);
    // getchar();

    Node *goal = nodes[FINISH_POINT.y][FINISH_POINT.x];

    std::vector<Node *> aStarPath = Algorithms::aStar(root, goal);
    // Виведення знайденого шляху A*
    // std::cout << "Path found by A*:\n";
    for (const Node *node: aStarPath) {
        // std::cout << "(" << node->x() << ", " << node->y() << ") ";
        maze[node->y()][node->x()] = WAY;
    }
    std::cout << "\n";

    Maze::printMaze(maze, START_POINT, FINISH_POINT);
    getchar();

    // // Виконання алгоритму BFS
    // std::vector<Node*> bfsPath = bfs(root, goal);
    // // Виведення знайденого шляху BFS
    // std::cout << "Path found by BFS:\n";
    // for (Node* node : bfsPath) {
    //     std::cout << "(" << node->x << ", " << node->y << ") ";
    // }
    // std::cout << "\n";

    Node::clearNodes(nodes);

    return 0;
}
