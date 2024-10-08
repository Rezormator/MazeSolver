#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <unordered_set>
#include "Input.h"
#include "Maze.h"
#include "Node.h"
#include "Algorithms.h"

constexpr int BFS_METHOD = 0;
constexpr int A_STAR_METHOD = 1;
constexpr int EXIT = 1;

int main() {
    // std::vector<int> nodesCount;
    // std::vector<std::vector<int>> iterationsCount(2, std::vector<int>(20, 0));
    // std::vector<std::vector<int>> visitedCount(2, std::vector<int>(20, 0));
    // std::vector<std::vector<std::chrono::duration<double> >> time(2, std::vector<std::chrono::duration<double> >());
    // std::vector<int> methods {BFS_METHOD, A_STAR_METHOD};
    //
    // for (int i = 0; i < 20; i++) {
    //     const auto mazeSize = 9 + i * 10;
    //     const Point start(1, 1);
    //     auto maze = Maze::createStartMaze(mazeSize, start);
    //     const Point finish(7 + i * 10, 7 + i * 10);
    //     std::vector nodes(mazeSize, std::vector<Node *>(mazeSize, nullptr));
    //     const auto root = Algorithms::mazeToTree(Node(start), maze, nodes);
    //     const auto finishNode = nodes[finish.y][finish.x];
    //     std::unordered_set<Node *> visited = {nodes[1][1]};
    //     nodesCount.push_back(root->countNodes(visited));
    //
    //     for (const auto method : methods) {
    //         auto startTime = std::chrono::high_resolution_clock::now();
    //         const auto path = method == BFS_METHOD
    //                               ? Algorithms::bfs(root, finishNode, iterationsCount[method][i], visitedCount[method][i])
    //                               : Algorithms::aStar(root, finishNode, iterationsCount[method][i], visitedCount[method][i]);
    //         auto endTime = std::chrono::high_resolution_clock::now();
    //         time[method].emplace_back(endTime - startTime);
    //     }
    //
    //     Node::clearNodes(nodes);
    // }
    //
    // for (const auto method : methods) {
    //     std::cout << (method == BFS_METHOD ? "BFS method:" : "A* method:") << std::endl << std::endl;
    //     for (int i = 0; i < 20; i++) {
    //         std::cout << "Maze size: " << 9 + i * 10 << std::endl;
    //         std::cout << "Time: " << time[method][i] << std::endl;
    //         std::cout << "Iterations count: " << iterationsCount[method][i] << std::endl;
    //         std::cout << "Nodes count: " << nodesCount[i] << std::endl;
    //         std::cout << "Visited nodes count: " << visitedCount[method][i] << std::endl;
    //         std::cout << std::endl;
    //     }
    //     std::cout << std::endl;
    // }
    //
    // std::cout << std::endl << "Press any key..." << std::endl;
    // getchar();

    do {
        const auto mazeSize = Input::inputInt("Enter maze size: ");
        const auto xStart = Input::inputInt("Enter x coordinate of start: ");
        const auto yStart = Input::inputInt("Enter y coordinate of start: ");
        const Point start(xStart, yStart);

        auto maze = Maze::createStartMaze(mazeSize, start);
        getchar();
        Maze::printMaze(maze, start);
        getchar();

        const auto xFinish = Input::inputInt("Enter x coordinate of finish: ");
        const auto yFinish = Input::inputInt("Enter y coordinate of finish: ");
        const Point finish(xFinish, yFinish);

        Maze::printMaze(maze, start, finish, true);
        getchar();
        getchar();

        const auto solvingMethod = Input::indexMenu({"BFS solver", "A* solver"});

        Maze::printMaze(maze, start, finish, true);

        std::vector nodes(mazeSize, std::vector<Node *>(mazeSize, nullptr));
        const auto root = Algorithms::mazeToTree(Node(start), maze, nodes);
        const auto finishNode = nodes[finish.y][finish.x];

        // std::vector<std::vector<bool>> visited(MAZE_SIZE, std::vector<bool>(MAZE_SIZE, false));
        // root->printTree(MAZE_SIZE);
        // getchar();

        std::unordered_set<Node *> visited = {nodes[1][1]};
        const auto nodesCount = root->countNodes(visited);
        int iterationsCount = 0;
        int visitedCount = 0;

        std::cout << "Solving with " << (solvingMethod == BFS_METHOD ? "BFS" : "A*") << " method..." << std::endl;
        auto startTime = std::chrono::high_resolution_clock::now();
        const auto path = solvingMethod == BFS_METHOD
                              ? Algorithms::bfs(root, finishNode, iterationsCount, visitedCount)
                              : Algorithms::aStar(root, finishNode, iterationsCount, visitedCount);
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time = endTime - startTime;

        for (const Node *node: path)
            maze[node->y()][node->x()] = WAY;
        std::cout << "\n";

        Maze::printMaze(maze, start, finish, true);

        std::cout << "Path fined by " << (solvingMethod == BFS_METHOD ? "BFS" : "A*") << " method:" << std::endl;
        for (const Node *node: path)
            std::cout << "(" << node->x() << ", " << node->y() << ") -> ";
        std::cout << "\n";

        std::cout << "Time: " << time << std::endl;
        std::cout << "Iterations count: " << iterationsCount << std::endl;
        std::cout << "Nodes count: " << nodesCount << std::endl;
        std::cout << "Visited nodes count: " << visitedCount << std::endl;

        Node::clearNodes(nodes);
        std::cout << std::endl << "Press any key..." << std::endl;
        getchar();
    } while (Input::indexMenu({"Try again"}, true) != EXIT);

    return 0;
}
