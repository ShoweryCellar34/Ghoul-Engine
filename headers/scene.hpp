#pragma once

#include <node.hpp>

struct scene : node {
private:
    nodeID m_IDCounter;

    nodeID newID();
    friend struct node;
public:

};
