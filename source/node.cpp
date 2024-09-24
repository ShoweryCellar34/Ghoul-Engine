#include <node.hpp>

#include <imguiDraw.hpp>
#include <defines_and_globals.hpp>

// Node definitions

void treeNode::selectNode(nodeRef node) {
    m_selectedNode = node;
}

nodeRef treeNode::getSelectedNode() {
    return m_selectedNode;
}

treeNode::treeNode(nodeRef root, nodeRef parent, nlohmann::json data, std::string name) : m_parent(parent), m_data(data), m_name(name), 
        m_imguiName(m_name + "##" + std::to_string((std::uintptr_t)this)), m_selectedFlag(0), m_shouldOpen(false), m_selectedNode(nullptr) {
    if(root == nullptr) {
        m_root = this;
    } else {
        m_root = root;
    }
}

treeNode::treeNode(nodeRef root, nodeRef parent, nlohmann::json json) : m_parent(parent), m_selectedFlag(0), m_shouldOpen(false), m_selectedNode(nullptr) {
    if(root == nullptr) {
        m_root = this;
    } else {
        m_root = root;
    }

    if(json.contains("name") && json["name"].is_string()) {
        setName(json.at("name").get<std::string>().c_str());
    }
    if (json.contains("data") && json["data"].is_string()) {
        m_data = json.at("data").get<std::string>();
    }

    if(json.contains("children") && json["children"].is_array()) {
        for (const auto& childJson : json.at("children")) {
            nodeRef childNode = new treeNode(m_root, this, childJson);
            m_children.push_back(childNode);
        }
    }
}

treeNode::~treeNode() {
    for(nodeRef child : m_children) {
        delete child;
    }
}

void treeNode::setName(std::string name) {
    m_name = name;
    m_imguiName = m_name + "##" + std::to_string((std::uintptr_t)this);
}

nodeRef treeNode::addChild(std::string name) {
    std::function<std::string(nodeRef, std::string, int)> nameCheck = [](nodeRef node, std::string name, int attempt){
        std::string goodName = name;
        for(nodeRef child : node->getChildren()) {
            if(child->getName() == name) {
                std::string fixedName = name + " (" + std::to_string(attempt) + ")";
                goodName = nameCheck(node, fixedName, attempt + 1);
            }
        }
        return goodName;
    };
    nodeRef child = new treeNode(m_root, (nodeRef)this, "", nameCheck(this, name, 1));
    m_children.push_back(child);
    return child;
}

nodeRef treeNode::addChild(nlohmann::json data) {
    nodeRef child = new treeNode(m_root, (nodeRef)this, data);
    m_children.push_back(child);
    return child;
}

void treeNode::reparent(nodeRef newParent) {
    m_parent = newParent;
    newParent->m_children.push_back(this);
    m_children.erase(std::find(m_children.begin(), m_children.end(), (nodeRef)this));
}

const char* treeNode::getName() const {
    return m_name.c_str();
}

nodeRef treeNode::getChild(std::string name) const {
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
        children.push_back(child->getJSON());
    }
    json["children"] = children;

    return json;
}

void treeNode::loadJSON(nlohmann::json json) {
    if(json.contains("name") && json["name"].is_string()) {
        setName(json.at("name").get<std::string>());
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
            m_children.push_back(childNode);
        }
    }
}

void drawNodePopup(const nodeRef node) {
    static bool renaming = false;
    static std::string newName;
    if(ImGui::Button("Add child")) {
        nodeRef child = node->addChild("child " + std::to_string(node->m_children.size()));
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
        if(drawRenameWindow(&renaming, &node->m_name, &newName, (std::string)"Rename " + node->m_imguiName)) {
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
