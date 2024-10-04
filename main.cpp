#include <iostream>
#include <vector>
#include <random>
#include "Input.h"
#include "Maze.h"
#include "Node.h"
#include "Algorithms.h"

constexpr int BFS_METHOD = 0;
constexpr int A_STAR_METHOD = 1;

int main() {
    const auto mazeSize = Input::inputInt("Enter maze size: ");
    const auto xStart = Input::inputInt("Enter x coordinate of start: ");
    const auto yStart = Input::inputInt("Enter y coordinate of start: ");
    Point start(xStart, yStart);

    auto maze = Maze::createStartMaze(mazeSize, start);
    Maze::printMaze(maze, start);
    getchar();

    const auto xFinish = Input::inputInt("Enter x coordinate of finish: ");
    const auto yFinish = Input::inputInt("Enter y coordinate of finish: ");
    Point finish(xFinish, yFinish);

    Maze::printMaze(maze, start, finish, true);
    getchar();

    const auto solvingMethod = Input::indexMenu({"BFS solver", "A* solver"});

    Maze::printMaze(maze, start, finish, true);
    std::cout << "Solving with " << (solvingMethod == BFS_METHOD ? "BFS" : "A*") << " method..." << std::endl;

    std::vector nodes(mazeSize, std::vector<Node *>(mazeSize, nullptr));
    const auto root = Algorithms::mazeToTree(Node(start), maze, nodes);

    // std::vector<std::vector<bool>> visited(MAZE_SIZE, std::vector<bool>(MAZE_SIZE, false));
    // root->printTree(MAZE_SIZE);
    // getchar();

    const auto finishNode = nodes[finish.y][finish.x];

    const auto path = solvingMethod == BFS_METHOD
                          ? Algorithms::bfs(root, finishNode)
                          : Algorithms::aStar(root, finishNode);

    for (const Node *node: path)
        maze[node->y()][node->x()] = WAY;
    std::cout << "\n";

    Maze::printMaze(maze, start, finish, true);

    std::cout << "Path fined by " << (solvingMethod == BFS_METHOD ? "BFS" : "A*") << " method:" << std::endl;
    for (const Node *node: path)
        std::cout << "(" << node->x() << ", " << node->y() << ") -> ";
    std::cout << "\n";

    Node::clearNodes(nodes);
    getchar();

    return 0;
}
