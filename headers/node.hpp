#pragma once

#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include <Pentagram.hpp>
#include <defines.hpp>

typedef size_t nodeID;

struct node {
private:
    nodeRef m_root;
    nodeRef m_parent;
    nlohmann::json m_data;
    std::string m_name;
    std::string m_imguiName;
    std::vector<nodeRef> m_children;
    mutable int m_selectedFlag;
    mutable bool m_shouldOpen;
    nodeRef m_selectedNode;

    friend void drawPopup(nodeRef node);
    friend void drawNodeInspector(const PNT::Window& window, nodeRef nodeToInspect);
    friend void drawNodeTree(const PNT::Window& window, nodeRef nodeToDraw);

    void selectNode(nodeRef node);
    nodeRef getSelectedNode();
public:
    node(nodeRef root, nodeRef parent, const char* data, const char* name);
    ~node();

    void setName(const char* name);
    void addChild(const char* name);
    void reparent(nodeRef newParent);

    const char* getName() const;
    nodeRef getChild(const char* name) const;
    nodeRef getParent() const;

    nlohmann::json getJSON() const;
    void imguiDraw() const;
};
