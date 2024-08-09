#pragma once

#include <unordered_map>
#include <node.hpp>

struct scene {
private:
    char* name;
    std::unordered_map<size_t, node*> nodes;
    std::vector<node*> nodesVector;
    size_t nodeIDCounter;

    node* newNode(node* parent, const char* name);
    friend struct node;
public:
    scene(const char* name);
    ~scene();

    node* addChild();
    node* addChild(const char* name);
    bool deleteChild(const char* name);
    bool deleteChild(size_t ID);
    void setName(const char* name);

    std::vector<node*> getNodes() const;
    std::vector<node*> getChildren() const;
    node* getNode(const char* name) const;
    node* getNode(size_t ID) const;
    node* getNodeRecursive(const char* name) const;
    node* getNodeRecursive(size_t ID) const;
    const char* getTitle() const;
};
