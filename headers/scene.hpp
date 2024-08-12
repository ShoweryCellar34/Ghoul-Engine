#pragma once

#include <unordered_map>
#include <vector>

struct node;

typedef size_t nodeID;

struct scene {
private:
    char* name;
    std::unordered_map<nodeID, node*> nodes;
    std::vector<nodeID> children;
    nodeID selectedNode;
    nodeID nodeIDCounter;

    friend struct node;
public:
    scene(const char* name);
    ~scene();

    nodeID newNode(nodeID parent, const char* name);
    void deleteNode(nodeID ID);
    void selectID(nodeID ID);

    nodeID getSelectedID() const;
    node* getNode(nodeID ID) const;

    void setName(const char* title);
    nodeID addChild(const char* name);
    bool removeChild(nodeID ID);

    const char* getName() const;
    std::vector<nodeID> getChildren() const;

};
