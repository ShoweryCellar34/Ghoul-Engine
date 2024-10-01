#include <node.hpp>

#include <format>
#include <imguiDraw.hpp>
#include <defines_and_globals.hpp>

namespace GH {
    std::string nameCheck(const nodeRef node, const std::string& name) {
        if(node->getParent() == nullptr) {
            return name;
        }

        std::string newString = name;
        int count = 1;

        std::vector<std::string> stringVector;
        stringVector.reserve(node->getParent()->getChildren().size());
        for(nodeRef child : node->getParent()->getChildren()) {
            if(child != node) {
                stringVector.emplace_back(child->getName());
            }
        }

        while (std::find(stringVector.begin(), stringVector.end(), newString) != stringVector.end()) {
            newString = name + std::format(" ({})", count);
            count++;
        }

        return newString;
    }

    // Node definitions

    void treeNode::selectNode(nodeRef node) {
        m_selectedNode = node;
    }

    nodeRef treeNode::getSelectedNode() {
        return m_selectedNode;
    }

    treeNode::treeNode(const nodeRef root, const nodeRef parent, const nlohmann::json& data, const std::string& name) : m_parent(parent), m_children{}, m_data(data), m_selectedFlag(0), m_shouldOpen(false) {
        if(root == nullptr) {
            m_root = this;
            m_selectedNode = this;
        } else {
            m_root = root;
            m_selectedNode = nullptr;
        }
        if(parent != nullptr) {
            m_name = nameCheck(this, name);
        } else {
            m_name = name;
        }
        m_imguiName = m_name + std::format("##{}", (std::uintptr_t)this);
    }

    treeNode::treeNode(const nodeRef root, const nodeRef parent, const nlohmann::json& json) : m_parent(parent), m_children{}, m_selectedFlag(0), m_shouldOpen(false) {
        if(root == nullptr) {
            m_root = this;
            m_selectedNode = this;
        } else {
            m_root = root;
            m_selectedNode = nullptr;
        }

        if(json.contains("name") && json["name"].is_string()) {
            setName(json.at("name").get<std::string>());
        }
        if (json.contains("data") && json["data"].is_string()) {
            m_data = json.at("data").get<std::string>();
        }

        if(json.contains("children") && json["children"].is_array()) {
            for (const auto& childJson : json.at("children")) {
                nodeRef childNode = new treeNode(m_root, this, childJson);
                m_children.emplace_back(childNode);
            }
        }
    }

    treeNode::~treeNode() {
        for(nodeRef child : m_children) {
            delete child;
        }
    }

    void treeNode::setName(const std::string& name) {
        if((name == "") or (name == m_name)) {
            return;
        }
        m_name = nameCheck(this, name);
        m_imguiName = m_name + std::format("##{}", (std::uintptr_t)this);
    }

    void treeNode::updateImGuiName() {
        m_imguiName = m_name + std::format("##{}", (std::uintptr_t)this);
    }

    nodeRef treeNode::addChild(const std::string& name) {
        nodeRef child = new treeNode(m_root, (nodeRef)this, "", name);
        m_children.emplace_back(child);
        return child;
    }

    nodeRef treeNode::addChild(const nlohmann::json& data) {
        nodeRef child = new treeNode(m_root, (nodeRef)this, data);
        m_children.emplace_back(child);
        return child;
    }

    bool treeNode::removeChild(const std::string& name) {
        bool found = false;
        for(nodeRef child : m_children) {
            if(child->getName() == name) {
                found = true;
                delete child;
                m_children.erase(std::find(m_children.begin(), m_children.end(), child));
            }
        }
        return found;
    }

    void treeNode::removeSelf() {
        if(m_parent != nullptr) {
            m_parent->removeChild(m_name);
        }
    }

    void treeNode::reparent(const nodeRef newParent) {
        m_parent = newParent;
        newParent->m_children.emplace_back(this);
        if(m_parent != nullptr) {
            m_children.erase(std::find(m_children.begin(), m_children.end(), (nodeRef)this));
        }
    }

    std::string treeNode::getName() const {
        return m_name;
    }

    std::string treeNode::getImGuiName() const {
        return m_imguiName;
    }

    nodeRef treeNode::getChild(const std::string& name) const {
        nodeRef result = nullptr;
        for(nodeRef child : m_children) {
            if(child->m_name == name) {
                result = child;
            }
        }
        return result;
    }

    std::vector<nodeRef> treeNode::getChildren() const {
        return m_children;
    }

    nodeRef treeNode::getParent() const {
        return m_parent;
    }

    nlohmann::json treeNode::getJSON() const {
        nlohmann::json json;
        json["name"] = m_name;
        json["data"] = m_data;

        nlohmann::json children = nlohmann::json::array();
        for(nodeRef child : m_children) {
            children.emplace_back(child->getJSON());
        }
        json["children"] = children;

        return json;
    }

    void treeNode::loadJSON(const nlohmann::json& json) {
        if(json.contains("name") && json["name"].is_string()) {
            setName(nameCheck(this, json.at("name").get<std::string>()));
        }
        if (json.contains("data") && json["data"].is_string()) {
            m_data = json.at("data").get<std::string>();
        }

        for(nodeRef child : m_children) {
            delete child;
        }
        m_children.clear();
        if(json.contains("children") && json["children"].is_array()) {
            for (const auto& childJson : json.at("children")) {
                nodeRef childNode = new treeNode(m_root, this, childJson);
                m_children.emplace_back(childNode);
            }
        }
    }

    void drawNodePopup(const nodeRef node) {
        static bool renaming = false;
        static std::string newName;
        if(ImGui::Button("Add child")) {
            nodeRef child = node->addChild((std::string)"child");
            node->m_root->selectNode(child);
            node->m_shouldOpen = true;
            ImGui::CloseCurrentPopup();
        }
        if(ImGui::Button("Rename")) {
            renaming = true;
            newName = node->getName();
        }
        if(ImGui::Button("Copy")) {
            g_nodeClipboard = node->getJSON();
            ImGui::CloseCurrentPopup();
        }
        if(ImGui::Button("Cut")) {
            g_nodeClipboard = node->getJSON();
            node->removeSelf();
            ImGui::CloseCurrentPopup();
        }
        if(ImGui::Button("Paste")) {
            if(!g_nodeClipboard.empty()) {
                nodeRef child = node->addChild(g_nodeClipboard);
                node->m_root->selectNode(child);
                node->m_shouldOpen = true;
            }
            ImGui::CloseCurrentPopup();
        }
        if(ImGui::Button("Remove")) {
            nodeRef parent = node->m_parent;
            parent->m_children.erase(std::find(parent->m_children.begin(), parent->m_children.end(), node));
            node->m_root->selectNode(nullptr);
            delete node;
            ImGui::CloseCurrentPopup();
        }
        if(renaming) {
            if(drawRenameWindow(&renaming, &node->m_name, &newName, "Rename Scene") == RENAME_STATUS::SUCCESS) {
                node->setName(node->getName());
                ImGui::CloseCurrentPopup();
            }
        }
    }

    void treeNode::imguiDraw() const {
        if(m_root->getSelectedNode() == this) {
            m_selectedFlag = ImGuiTreeNodeFlags_Selected;
        } else {
            m_selectedFlag = ImGuiTreeNodeFlags_None;
        }

        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | m_selectedFlag;
        if(m_children.size() == 0) {
            flags |= ImGuiTreeNodeFlags_Leaf;
        }
        if(m_shouldOpen) {
            ImGui::SetNextItemOpen(true);
            m_shouldOpen = false;
        }
        if(ImGui::TreeNodeEx(m_imguiName.c_str(), flags)) {
            if(ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
                m_root->selectNode((nodeRef)this);
            }
            if(ImGui::BeginPopupContextItem()) {
                m_root->selectNode((nodeRef)this);
                drawNodePopup((nodeRef)this);
                ImGui::EndPopup();
            }

            for(nodeRef child : m_children) {
                child->imguiDraw();
            }
            ImGui::TreePop();
        } else {
            if(ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
                m_root->selectNode((nodeRef)this);
            }
            if(ImGui::BeginPopupContextItem()) {
                m_root->selectNode((nodeRef)this);
                drawNodePopup((nodeRef)this);
                ImGui::EndPopup();
            }
        }
    }
}
