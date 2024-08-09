#pragma once

#include <unordered_map>
#include <vector>

struct node;

struct scene {
private:
    char* title;
    std::unordered_map<size_t, node*> nodes;
    std::vector<size_t> children;
    size_t selectedNode;
    size_t nodeIDCounter;

    friend struct node;
public:
    scene(const char* name);
    ~scene();

    node* newNode(node* parent, const char* name);
    void deleteNode(size_t ID);
    void selectID(size_t ID);
    void setTitle(const char* name);

    size_t getSelectedID();
    node* getNode(size_t ID);
    const char* getTitle();
    std::vector<node*> getChildren();

};
