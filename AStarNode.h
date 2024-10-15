#pragma once

#include "Node.h"

#define NODISCARD [[nodiscard]]

class AStarNode {
private:
    Node *node;
    double g;
    double h;
    double f;
public:
    AStarNode(Node *n, double g, double h);

    NODISCARD Node *getNode() const;
    NODISCARD double getG() const;
    NODISCARD double getH() const;
    NODISCARD double getF() const;

    bool operator>(const AStarNode &other) const;
};
