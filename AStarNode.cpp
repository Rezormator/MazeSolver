#include "AStarNode.h"

AStarNode::AStarNode(Node *n, const double g, const double h) : node(n), g(g), h(h), f(g + h) {
}

Node *AStarNode::getNode() const {
    return node;
}

double AStarNode::getG() const {
    return g;
}

double AStarNode::getH() const {
    return h;
}

double AStarNode::getF() const {
    return f;
}

bool AStarNode::operator>(const AStarNode &other) const {
    return f > other.f;
}