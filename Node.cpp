#include "Node.h"
#include <iostream>

Node::Node(const Point node) : node(node) {
}

Point Node::getNode() const {
    return node;
}

std::vector<Node *> Node::getChildrens() const {
    return childrens;
}

int Node::x() const {
    return node.x;
}

int Node::y() const {
    return node.y;
}

int Node::countNodes(std::unordered_set<Node *> &visited) const {
    int count = 1;
    for (const auto child: childrens)
        if (child && !visited.contains(child)) {
            visited.insert(child);
            count += child->countNodes(visited);
        }
    return count;
}

void Node::addChildren(Node *children) {
    if (children && std::ranges::find(childrens, children) == childrens.end())
        childrens.push_back(children);
}

void Node::printTree(const int mazeSize) const {
    std::vector visited(mazeSize, std::vector(mazeSize, false));
    printNode(*this, visited, 1);
}

void Node::clearNodes(const std::vector<std::vector<Node *> > &nodes) {
    for (int y = 0; y < nodes.size(); y++)
        for (int x = 0; x < nodes.size(); x++)
            delete nodes[y][x];
}

void Node::printNode(const Node &root, std::vector<std::vector<bool> > &visited, const int level) const {
    if (visited[root.getNode().y][root.getNode().x])
        return;

    visited[root.y()][root.x()] = true;
    std::cout << level << " -> (" << root.getNode().x << ", " << root.getNode().y << ")\n";

    for (const auto &neighbor: root.getChildrens())
        printNode(*neighbor, visited, level + 1);
}
