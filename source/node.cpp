#include <node.hpp>

#include <imgui.h>
#include <cstring>
#include <string>
#include <iostream>

node::node(node* parent) : parent(parent), ID(instances), selected(ImGuiTreeNodeFlags_None) {
    instances++;
    setName("Unnamed");
}

node::node(node *parent, const char* name) : parent(parent), ID(instances), selected(ImGuiTreeNodeFlags_None) {
    instances++;
    setName(name);
}

node::~node() {
    delete[] imguiName;
    for(node* node : children) {
        delete node;
    }
}

void node::addChild() {
    children.push_back(new node(this));
}

void node::addChild(const char* name) {
    children.push_back(new node(this, name));
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
    if(strlen(name) < 256) {
        strcpy(this->name, name);
    } else {
        for(int i; i < 256; i++) {
            this->name[i] = name[i];
        }
    }
    imguiName = new char[strlen(this->name) + 2 + strlen(std::to_string(ID).c_str())];
    strcpy(imguiName, this->name);
    strcat(imguiName, "##");
    strcat(imguiName, std::to_string(ID).c_str());
}

std::vector<node*> node::getChildren() {
    return children;
}

node *node::getChild(const char* name) {
    for(node* node : children) {
        if(node->getName() == name) {
            return node;
        }
    }
    return nullptr;
}

node *node::getChild(size_t ID) {
    for(node* node : children) {
        if(node->getID() == ID) {
            return node;
        }
    }
    return nullptr;
}

const char* node::getName() {
    return name;
}

size_t node::getID() {
    return ID;
}

void node::ImGuiDraw() {
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | selected;
    if(children.size() == 0) {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }
    if(ImGui::TreeNodeEx(imguiName, flags)) {
        if(ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
            selectedID = ID;
        }
        for(node* child : children) {
            child->ImGuiDraw();
        }
        ImGui::TreePop();
    }
    if(selectedID == ID) {
        selected = ImGuiTreeNodeFlags_Selected;
    } else {
        selected = ImGuiTreeNodeFlags_None;
    }
}
