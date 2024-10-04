#pragma once

#include "Node.h"

#define NODISCARD [[nodiscard]]

class AStarNode {
private:
    Node *node;
    double g; // Відстань від стартового вузла
    double h; // Оцінка відстані до цільового вузла
    double f; // g + h (сумарна вартість)
public:
    AStarNode(Node *n, double g, double h);

    NODISCARD Node *getNode() const;
    NODISCARD double getG() const;
    NODISCARD double getH() const;
    NODISCARD double getF() const;

    bool operator>(const AStarNode &other) const;
};
