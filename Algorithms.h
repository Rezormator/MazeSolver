#pragma once

#include "Point.h"
#include "Node.h"
#include <vector>

typedef std::vector<std::vector<Node *> > nodes;

class Algorithms {
private:
    static Node *buildTree(int x, int y, const maze &maze, nodes &nodes);
public:
    static Node *mazeToTree(const Node &start, const maze &maze, nodes &nodes);
    static std::vector<Node *> bfs(Node *start, const Node *finish);
    static double euclideanDistance(const Node *a, const Node *b);
    static std::vector<Node *> aStar(Node *start, const Node *finish);
};
