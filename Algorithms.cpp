#include "Algorithms.h"
#include "AStarNode.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <ranges>

Node *Algorithms::mazeToTree(const Node &start, const maze &maze, nodes &nodes) {
    return buildTree(start.x(), start.y(), maze, nodes);
}

Node *Algorithms::buildTree(const int x, const int y, const maze &maze, nodes &nodes) {
    if (maze[y][x] != PATH)
        return nullptr;

    if (nodes[y][x])
        return nodes[y][x];

    nodes[y][x] = new Node(Point(x, y));

    if (x > 0 && maze[y][x - 1] == PATH)
        nodes[y][x]->addChildren(buildTree(x - 1, y, maze, nodes));
    if (x < maze.size() - 1 && maze[y][x + 1] == PATH)
        nodes[y][x]->addChildren(buildTree(x + 1, y, maze, nodes));
    if (y > 0 && maze[y - 1][x] == PATH)
        nodes[y][x]->addChildren(buildTree(x, y - 1, maze, nodes));
    if (y < maze.size() - 1 && maze[y + 1][x] == PATH)
        nodes[y][x]->addChildren(buildTree(x, y + 1, maze, nodes));

    return nodes[y][x];
}

double Algorithms::euclideanDistance(const Node *a, const Node *b) {
    return std::sqrt(std::pow(b->x() - a->x(), 2) + std::pow(b->y() - a->y(), 2));
}

std::vector<Node *> Algorithms::aStar(Node *start, const Node *finish) {
    std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<> > set;
    std::unordered_set<Node *> visited;
    std::unordered_map<Node *, Node *> parentOf;
    std::unordered_map<Node *, int> gOf;

    set.emplace(start, 0, euclideanDistance(start, finish));
    gOf[start] = 0;

    while (!set.empty()) {
        Node *current = set.top().getNode();
        set.pop();

        if (current == finish) {
            std::vector<Node *> path;
            for (Node *node = current; node != nullptr; node = parentOf[node])
                path.push_back(node);
            std::ranges::reverse(path);
            return path;
        }

        visited.insert(current);

        for (const auto& children : current->getChildrens()) {
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

std::vector<Node *> Algorithms::bfs(Node *start, const Node *finish) {
    std::queue<Node *, std::vector<Node *>> set;
    std::unordered_set<Node *> visited;
    std::unordered_map<Node *, Node *> parentOf;

    set.emplace(start, 0, euclideanDistance(start, finish));

    while (!set.empty()) {
        Node *current = set.front();
        set.pop();

        if (current == finish) {
            std::vector<Node *> path;
            for (Node *node = current; node != nullptr; node = parentOf[node])
                path.push_back(node);
            std::ranges::reverse(path);
            return path;
        }

        visited.insert(current);

        for (const auto& children : current->getChildrens()) {
            if (visited.contains(children))
                continue;

            set.push(children);
            parentOf[children] = current;
        }
    }

    return {};
}
