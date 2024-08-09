#pragma once

#include <unordered_map>
#include <vector>

struct node;

struct scene {
private:
    char* name;
    std::unordered_map<size_t, node*> nodes;
    size_t selectedNode;
    size_t nodeIDCounter;
    static inline node* selectedNode = nullptr;

    node* newNode(node* parent, const char* name);
    void deleteNode(size_t ID);
    friend struct node;
public:
    scene(const char* name);
    ~scene();

    node* addChild();
    node* addChild(const char* name);
    bool deleteChild(const char* name);
    bool deleteChild(size_t ID);
    void setName(const char* name);
};
