#pragma once

#include <unordered_map>
#include <vector>
#include <scene.hpp>

namespace PNT {
    class Window;
}

struct node {
private:
    scene* parentScene;
    size_t ID;
    char* name;
    std::vector<node*> children;
    mutable int selectedFlag;
    char* imguiName;
    node* parent;
    mutable bool shouldOpen;

    friend void drawNodeInspector(const PNT::Window& window);
    friend void drawPopup(node* node);
public:
    node(scene* scene, node* node, size_t ID, const char* name);
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
