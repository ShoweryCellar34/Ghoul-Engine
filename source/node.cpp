#include <node.hpp>

#include <imgui.h>
#include <cstring>
#include <string>

node::node(node* parent) : parent(parent), ID(instances), name{"Unnamed"} {
    instances++;
}

node::node(node *parent, const char* name) : parent(parent), ID(instances) {
    instances++;
    setName(name);
}

node::~node() {
    instances--;
    for(node* node : children) {
        delete node;
    }
}

void node::addChild() {
    children.push_back(new node(this));
}

void node::addChild(const char *name) {
    children.push_back(new node(this, name));
}

void node::setName(const char *name) {
    if(strlen(name) <= 256) {
        strcpy(this->name, name);
    } else {
        for(int i; i < 256; i++) {
            this->name[i] = name[i];
        }
    }
}

std::vector<node*> node::getChildren() {
    return children;
}

node *node::getChild(const char *name) {
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
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_NavLeftJumpsBackHere | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
    if(children.size() < 1) {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }
    char* name = new char[strlen(this->name) + 2 + strlen(std::to_string(ID).c_str())];
    strcpy(name, this->name);
    strcat(name, "##");
    strcat(name, std::to_string(ID).c_str());
    if(ImGui::TreeNodeEx(name, flags)) {
        if(children.size() > 0) {
            for(node* child : children) {
                child->ImGuiDraw();
            }
        }

        ImGui::TreePop();
    }
    delete name;
}
