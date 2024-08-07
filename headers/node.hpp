#pragma once

#include <unordered_map>
#include <vector>

namespace PNT {
    class Window;
}

struct node {
private:
    static inline size_t instances;
    static inline std::unordered_map<size_t, node*> instancesList;
    static inline node* selectedNode = nullptr;
    mutable int selectedFlag;
    size_t ID;
    char* name;
    char* imguiName;
    node* parent;
    mutable bool shouldOpen;
    std::vector<node*> children;

    friend void drawNodeInspector(const PNT::Window& window);
    friend void drawPopup(node* node);
public:
    node(node* parent);
    node(node* parent, const char* name);
    ~node();

    node* addChild();
    node* addChild(const char* name);
    bool deleteChild(const char* name);
    bool deleteChild(size_t ID);
    void setName(const char* name);
    node* reparent(size_t ID);

    std::vector<node*> getChildren() const;
    node* getChild(const char* name) const;
    node* getChild(size_t ID) const;
    const char* getName() const;
    size_t getID() const;
    node* getParent() const;

    void ImGuiDraw() const;
};
