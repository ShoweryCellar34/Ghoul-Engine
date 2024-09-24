#pragma once

#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include <Pentagram.hpp>
#include <defines_and_globals.hpp>

struct treeNode {
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

    friend void drawMainMenuBar();
    friend void drawNodePopup(nodeRef node);
    friend void drawScenePopup(nodeRef node);
    friend void drawNodeInspector(const nodeRef nodeToInspect);
    friend void drawNodeTree(const nodeRef nodeToDraw);
    friend void eventCallback(PNT::Window* window, PNT::windowEvent event);

    void selectNode(nodeRef node);
    nodeRef getSelectedNode();
public:
    treeNode(nodeRef root, nodeRef parent, nlohmann::json data, std::string name);
    treeNode(nodeRef root, nodeRef parent, nlohmann::json json);
    ~treeNode();

    void setName(std::string name);
    nodeRef addChild(std::string name);
    nodeRef addChild(nlohmann::json data);
    bool removeChild(std::string name);
    void reparent(nodeRef newParent);

    const char* getName() const;
    nodeRef getChild(std::string name) const;
    std::vector<nodeRef> getChildren() const;
    nodeRef getParent() const;

    nlohmann::json getJSON() const;
    void loadJSON(nlohmann::json json);
    void imguiDraw() const;
};
