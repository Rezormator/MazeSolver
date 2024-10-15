#include "Algorithms.h"
#include "AStarNode.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <ranges>
#include <iostream>

Node *Algorithms::mazeToGraph(const Node &start, const maze &maze, nodes &nodes) {
    return buildGraph(start.x(), start.y(), maze, nodes);
}

Node *Algorithms::buildGraph(const int x, const int y, const maze &maze, nodes &nodes) {
    if (maze[y][x] != PATH)
        return nullptr;

    if (nodes[y][x])
        return nodes[y][x];

    nodes[y][x] = new Node(Point(x, y));

    if (x > 0 && maze[y][x - 1] == PATH)
        nodes[y][x]->addChildren(buildGraph(x - 1, y, maze, nodes));

    if (x < maze.size() - 1 && maze[y][x + 1] == PATH)
        nodes[y][x]->addChildren(buildGraph(x + 1, y, maze, nodes));

    if (y > 0 && maze[y - 1][x] == PATH)
        nodes[y][x]->addChildren(buildGraph(x, y - 1, maze, nodes));

    if (y < maze.size() - 1 && maze[y + 1][x] == PATH)
        nodes[y][x]->addChildren(buildGraph(x, y + 1, maze, nodes));

    return nodes[y][x];
}

std::vector<Node *> Algorithms::bfs(Node *start, const Node *finish, int &iterationsCount, int &visitedCount) {
    std::queue<Node *> set;
    std::unordered_set<Node *> visited;
    std::unordered_map<Node *, Node *> parentOf;

    set.push(start);

    while (!set.empty()) {
        iterationsCount++;
        Node *current = set.front();
        set.pop();

        // std::cout << "Node: (" << current->x() << "; " << current->y() << ")" << std::endl;
        // if (!parentOf.empty())
        //     std::cout << "Come from node: (" << parentOf[current]->x() << "; " << parentOf[current]->y() << ")" << std::endl;
        // int depth = 0;
        // for (Node *node = current; node != nullptr; node = parentOf[node])
        //     depth++;
        // std::cout << "Node depth: " << depth << std::endl;

        if (current == finish) {
            std::vector<Node *> path;
            for (Node *node = current; node != nullptr; node = parentOf[node])
                path.push_back(node);
            std::ranges::reverse(path);
            return path;
        }

        visited.insert(current);
        visitedCount++;

        for (const auto& children : current->getChildrens()) {
            iterationsCount++;
            if (visited.contains(children))
                continue;

            set.push(children);
            parentOf[children] = current;
        }
    }

    return {};
}

double Algorithms::euclideanDistance(const Node *a, const Node *b) {
    return std::sqrt(std::pow(b->x() - a->x(), 2) + std::pow(b->y() - a->y(), 2));
}

std::vector<Node *> Algorithms::aStar(Node *start, const Node *finish, int &iterationsCount, int &visitedCount) {
    std::priority_queue<AStarNode, std::deque<AStarNode>, std::greater<> > set;
    std::unordered_set<Node *> visited;
    std::unordered_map<Node *, Node *> parentOf;
    std::unordered_map<Node *, int> gOf;

    set.emplace(start, 0, euclideanDistance(start, finish));
    gOf[start] = 0;

    while (!set.empty()) {
        iterationsCount++;
        Node *current = set.top().getNode();
        set.pop();

        // std::cout << "Node: (" << current->x() << "; " << current->y() << ")" << std::endl;
        // if (!parentOf.empty())
        //     std::cout << "Come from node: (" << parentOf[current]->x() << "; " << parentOf[current]->y() << ")" << std::endl;
        // std::cout << "Node g: " << gOf[current] << std::endl;
        // std::cout << "Node h: " << euclideanDistance(current, finish) << std::endl;
        // std::cout << "Node f: " << gOf[current] + euclideanDistance(current, finish) << std::endl;

        if (current == finish) {
            std::vector<Node *> path;
            for (Node *node = current; node != nullptr; node = parentOf[node])
                path.push_back(node);
            std::ranges::reverse(path);
            return path;
        }

        visited.insert(current);
        visitedCount++;

        for (const auto& children : current->getChildrens()) {
            iterationsCount++;
            if (visited.contains(children))
                continue;

            double g = gOf[current] + 1;

            if (gOf.contains(children) && g >= gOf[children])
                continue;

            set.emplace(children, g, euclideanDistance(children, finish));
            gOf[children] = g;
            parentOf[children] = current;
        }
    }

    return {};
}
