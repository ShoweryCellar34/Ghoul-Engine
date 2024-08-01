#pragma once

#include <vector>

struct node {
private:
    static inline size_t instances;
    static inline size_t selectedID;
    int selected;
    size_t ID;
    char name[256];
    char* imguiName;
    node* parent;
    std::vector<node*> children;

public:
    node(node* parent);
    node(node* parent, const char* name);
    ~node();

    void addChild();
    void addChild(const char* name);
    bool deleteChild(const char* name);
    bool deleteChild(size_t ID);
    void setName(const char* name);

    std::vector<node*> getChildren();
    node* getChild(const char* name);
    node* getChild(size_t ID);
    node* getParent();
    const char* getName();
    size_t getID();

    void ImGuiDraw();
};
