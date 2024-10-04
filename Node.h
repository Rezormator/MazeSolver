#pragma once

#include <vector>
#include "Point.h"
#include "Maze.h"

#define NODISCARD [[nodiscard]]

class Node {
private:
    Point node;
    std::vector<Node *> childrens;

    void printNode(const Node& root, std::vector<std::vector<bool>>& visited, int level) const;
public:
    explicit Node(Point node);

    NODISCARD Point getNode() const;
    NODISCARD std::vector<Node *> getChildrens() const;
    NODISCARD int x() const;
    NODISCARD int y() const;

    void addChildren(Node *children);
    void printTree(int mazeSize) const;
    static void clearNodes(const std::vector<std::vector<Node *> > &nodes);
};
