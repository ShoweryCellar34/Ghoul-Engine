#pragma once

#include <node.hpp>

struct scene : node {
private:
    nodeID m_IDCounter;

    nodeID newID();
    friend struct node;

public:
    scene(std::string name);
    scene(const char* name);

    void load(std::string saveData);
    std::string save();
};
