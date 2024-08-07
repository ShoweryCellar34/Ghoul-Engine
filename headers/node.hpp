#pragma once

#include <vector>

namespace PNT {
    class Window;
}

struct node {
private:
    static inline size_t instances;
    static inline std::vector<node*> instancesList;
    static inline node* selectedNode;
    mutable int selectedFlag;
    size_t ID;
    char* name;
    char* imguiName;
    node* parent;
    std::vector<node*> children;

    friend void drawNodeInspector(const PNT::Window& window);
public:
    node(node* parent);
    node(node* parent, const char* name);
    ~node();

    void addChild();
    void addChild(const char* name);
    bool deleteChild(const char* name);
    bool deleteChild(size_t ID);
    void setName(const char* name);

    std::vector<node*> getChildren() const;
    node* getChild(const char* name) const;
    node* getChild(size_t ID) const;
    node* getParent() const;
    const char* getName() const;
    size_t getID() const;

    void ImGuiDraw() const;
};
