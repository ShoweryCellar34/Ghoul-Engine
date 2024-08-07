#include <node.hpp>

#include <cstring>
#include <algorithm>
#include <imgui.h>

node::node(node* parent) : parent(parent), ID(instances), selectedFlag(ImGuiTreeNodeFlags_None), name(new char[1]{0}), imguiName(new char[1]{0}) {
    instancesList.insert({ID, this});
    instances++;
    setName("Unnamed");
}

node::node(node *parent, const char* name) : parent(parent), ID(instances), selectedFlag(ImGuiTreeNodeFlags_None), name(new char[1]{0}), imguiName(new char[1]{0}) {
    instancesList.insert({ID, this});
    instances++;
    setName(name);
}

node::~node() {
    instances--;
    instancesList.erase(instancesList.find(ID));
    delete[] imguiName;
    for(node* node : children) {
        delete node;
    }
}

node* node::addChild() {
    children.push_back(new node(this));
    return children.at(children.size() - 1);
}

node* node::addChild(const char* name) {
    children.push_back(new node(this, name));
    return children.at(children.size() - 1);
}

bool node::deleteChild(const char* name) {
    for(node* node : children) {
        if(node->getName() == name) {
            delete node;
            return true;
        }
    }
    return false;
}

bool node::deleteChild(size_t ID) {
    for(node* node : children) {
        if(node->getID() == ID) {
            delete node;
            return true;
        }
    }
    return false;
}

void node::setName(const char *name) {
    delete[] this->name;
    if(strlen(name) > 0) {
        this->name = new char[strlen(name)];
        strcpy(this->name, name);
    } else {
        this->name = new char[1];
        this->name[0] = 0;
    }

    delete[] imguiName;
    imguiName = new char[strlen(this->name) + 2 + strlen(std::to_string(ID).c_str()) + 1];
    strcpy(imguiName, this->name);
    strcat(imguiName, "##");
    strcat(imguiName, std::to_string(ID).c_str());
}

node* node::reparent(size_t ID) {
    instancesList.at(ID)->children.push_back(this);
    parent->children.erase(std::find(parent->children.begin(), parent->children.end(), this));
    instancesList.erase(instancesList.find(ID));
    return nullptr;
}

std::vector<node*> node::getChildren() const {
    return children;
}

node* node::getChild(const char* name) const {
    for(node* node : children) {
        if(node->getName() == name) {
            return node;
        }
    }
    return nullptr;
}

node* node::getChild(size_t ID) const {
    for(node* node : children) {
        if(node->getID() == ID) {
            return node;
        }
    }
    return nullptr;
}

const char* node::getName() const {
    return name;
}

size_t node::getID() const {
    return ID;
}

std::string node::getPath() const {
    return std::string();
}

void node::ImGuiDraw() const {
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | selectedFlag;
    if(children.size() == 0) {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }
    if(ImGui::TreeNodeEx(imguiName, flags)) {
        if(ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
            selectedNode = (node*)this;
        }
        for(node* child : children) {
            child->ImGuiDraw();
        }
        ImGui::TreePop();
    }
    if(selectedNode == this) {
        selectedFlag = ImGuiTreeNodeFlags_Selected;
    } else {
        selectedFlag = ImGuiTreeNodeFlags_None;
    }
}
