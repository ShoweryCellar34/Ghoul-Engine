#pragma once

#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include <Pentagram.hpp>
#include <defines_and_globals.hpp>

void eventCallback(PNT::Window* window, PNT::windowEvent event);

namespace GH {
    struct node {
    private:
        nodeRef m_root;
        nodeRef m_parent;
        std::vector<nodeRef> m_children;
        nlohmann::json m_data;
        std::string m_name;
        std::string m_imguiName;
        mutable int m_selectedFlag;
        mutable bool m_shouldOpen;
        nodeRef m_selectedNode;

        friend void drawMainMenuBar();
        friend void drawNodePopup(nodeRef node);
        friend void drawScenePopup(nodeRef node);
        friend void drawNodeTree();
        friend void drawNodeInspector();
        friend void ::eventCallback(PNT::Window* window, PNT::windowEvent event);

    public:
        node(const nodeRef root, const nodeRef parent, const nlohmann::json& data, const std::string& name);
        node(const nodeRef root, const nodeRef parent, const nlohmann::json& json);
        ~node();
        node(const node&) = delete;
        node& operator=(const node&) = delete;

        void selectNode(const nodeRef node);
        void setName(const std::string& name);
        void updateImGuiName();
        nodeRef addChild(const std::string& name);
        nodeRef addChild(const nlohmann::json& data);
        bool removeChild(const std::string& name);
        void removeSelf();
        void reparent(const nodeRef newParent);

        nodeRef getSelectedNode();
        std::string getName() const;
        std::string getImGuiName() const;
        nodeRef getChild(const std::string& name) const;
        std::vector<nodeRef> getChildren() const;
        nodeRef getParent() const;

        nlohmann::json getJSON() const;
        void loadJSON(const nlohmann::json& json);
        void imguiDraw() const;
    };
}
