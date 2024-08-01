#pragma once

#include <vector>

struct node {
public:
    node(node* parent);
    node(node* parent, const char* name);
    ~node();

    void addChild();
    void addChild(const char* name);
    void setName(const char* name);

    std::vector<node*> getChildren();
    node* getChild(const char* name);
    node* getChild(size_t ID);
    const char* getName();
    size_t getID();

    void ImGuiDraw();

private:
    static inline size_t instances;
    size_t ID;
    char name[256];
    node* parent;
    std::vector<node*> children;
};
