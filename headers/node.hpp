#pragma once

#include <unordered_map>
#include <vector>
#include <scene.hpp>

// namespace PNT {
//     class Window;
// }

// struct node {
// private:
//     scene* parentScene;
//     size_t ID;
//     char* name;
//     std::vector<node*> children;
//     mutable int selectedFlag;
//     char* imguiName;
//     node* parent;
//     mutable bool shouldOpen;

//     friend void drawNodeInspector(const PNT::Window& window);
//     friend void drawPopup(node* node);
// public:
//     node(scene* scene, size_t nodeParent, size_t nodeID, const char* name);
//     node(scene* scene, size_t nodeParent, size_t nodeID);
//     ~node();

//     node* addChild();
//     node* addChild(const char* name);
//     bool deleteChild(const char* name);
//     bool deleteChild(size_t ID);
//     void setName(const char* name);
//     node* reparent(size_t ID);

//     std::vector<node*> getChildren() const;
//     node* getChild(const char* name) const;
//     node* getChild(size_t ID) const;
//     const char* getName() const;
//     size_t getID() const;
//     node* getParent() const;

//     void ImGuiDraw() const;
// };

struct node : scene {
private:
    scene* m_ParentScene;
    nodeID m_Parent;
    nodeID m_ID;
    char* m_Name;
    char* m_ImguiName;
    mutable int m_SelectedFlag;
    mutable bool m_ShouldOpen;

    friend void drawPopup(node* node);
public:
    nodeID newNode(nodeID parent, const char* name) = delete;
    void deleteNode(nodeID ID) = delete;
    void selectID(nodeID ID) = delete;
    nodeID getSelectedID() const = delete;
    node* getNode(nodeID ID) const = delete;

    node(scene* scene, nodeID parent, nodeID ID, const char* name);
    ~node();

    void setName(const char* name);
    void reparent(nodeID newParent);
    nodeID addChild(const char* name);

    nodeID getParent() const;
    nodeID getID() const;

    void ImDraw() const;
};
