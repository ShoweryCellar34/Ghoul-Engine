#include <node.hpp>

void node::selectNode(nodeRef node) {
    m_selectedNode = node;
}

nodeRef node::getSelectedNode() {
    return m_selectedNode;
}

node::node(nodeRef root, nodeRef parent, const char *data, const char *name) : m_parent(parent), m_data(data), m_name(name), m_imguiName(m_name + "##" + std::to_string((std::uintptr_t)this)), m_selectedFlag(0), m_shouldOpen(false), m_selectedNode(nullptr)
{
    if(root == nullptr) {
        m_root = (nodeRef)this;
    } else {
        m_root = root;
    }
}

node::~node() {
    for(nodeRef child : m_children) {
        delete child;
    }
}

void node::setName(const char* name) {
    m_name = name;
    m_imguiName = m_name + "##" + std::to_string((std::uintptr_t)this);
}

void node::addChild(const char* name) {
    m_children.push_back(new node(m_root, (nodeRef)this, "", name));
}

void node::reparent(nodeRef newParent) {
    m_parent = newParent;
    newParent->m_children.push_back(this);
    m_children.erase(std::find(m_children.begin(), m_children.end(), (nodeRef)this));
}

const char* node::getName() const {
    return m_name.c_str();
}

nodeRef node::getChild(const char* name) const {
    nodeRef result = nullptr;
    for(nodeRef child : m_children) {
        if(child->m_name == name) {
            result = child;
        }
    }
    return result;
}

nodeRef node::getParent() const {
    return m_parent;
}

nlohmann::json node::getJSON() const {
    nlohmann::json json;
    json["name"] = m_name;
    json["data"] = m_data;

    nlohmann::json children = nlohmann::json::array();
    for(nodeRef child : m_children) {
        children["children"].push_back(child->getJSON());
    }
    json["children"] = children;
    
    return json;
}

void drawPopup(nodeRef node) {
    if(ImGui::Button("Add child")) {
        node->addChild("child " + node->m_children.size());
        node->m_shouldOpen = true;
        ImGui::CloseCurrentPopup();
    }
    if(ImGui::Button("Remove")) {
        delete node;
        ImGui::CloseCurrentPopup();
    }
}

void node::imguiDraw() const {
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
            drawPopup((node*)this);
            ImGui::EndPopup();
        }

        for(nodeRef child : m_children) {
            child->imguiDraw();
        }
        ImGui::TreePop();
    } else {
        if(ImGui::BeginPopupContextItem()) {
            drawPopup((nodeRef)this);
            ImGui::EndPopup();
        }
    }

    if(m_root->getSelectedNode() == this) {
        m_selectedFlag = ImGuiTreeNodeFlags_Selected;
    } else {
        m_selectedFlag = ImGuiTreeNodeFlags_None;
    }
}
