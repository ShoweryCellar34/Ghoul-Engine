#include <node.hpp>

#include <cstring>
#include <string>
#include <algorithm>
#include <imgui.h>

node::node(node* parent) : selectedFlag(ImGuiTreeNodeFlags_None), ID(instances), name(nullptr), imguiName(nullptr), parent(parent), shouldOpen(false) {
    instancesList.insert({ID, this});
    instances++;
    setName("Unnamed");
}

node::node(node *parent, const char* name) : selectedFlag(ImGuiTreeNodeFlags_None), ID(instances), name(nullptr), imguiName(nullptr), parent(parent), shouldOpen(false) {
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
    node* child = new node(this);
    children.push_back(child);
    return child;
}

node* node::addChild(const char* name) {
    node* child = new node(this, name);
    children.push_back(child);
    return child;
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
    if(name != this->name) {
        if(this->name != nullptr) {
            delete[] this->name;
        }
        if(strlen(name) > 0) {
            this->name = new char[strlen(name)];
            strcpy(this->name, name);
        } else {
            this->name = new char[1];
            this->name[0] = 0;
        }

        if(this->imguiName != nullptr) {
            delete[] imguiName;
        }
        imguiName = new char[strlen(this->name) + 2 + strlen(std::to_string(ID).c_str()) + 1];
        strcpy(imguiName, this->name);
        strcat(imguiName, "##");
        strcat(imguiName, std::to_string(ID).c_str());
    }
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

node* node::getParent() const {
    return parent;
}

void drawPopup(node* node) {
    if(ImGui::Button("Add child")) {
        node->addChild();
        node->shouldOpen = true;
        ImGui::CloseCurrentPopup();
    }
}

void node::ImGuiDraw() const {
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | selectedFlag;
    if(children.size() == 0) {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }
    if(shouldOpen) {
        ImGui::SetNextItemOpen(true);
        shouldOpen = false;
    }
    if(ImGui::TreeNodeEx(imguiName, flags)) {
        if(ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
            selectedNode = (node*)this;
        }
        if(ImGui::BeginPopupContextItem()) {
            drawPopup((node*)this);
            ImGui::EndPopup();
        }

        for(node* child : children) {
            child->ImGuiDraw();
        }
        ImGui::TreePop();
    } else {
        if(ImGui::BeginPopupContextItem()) {
            drawPopup((node*)this);
            ImGui::EndPopup();
        }
    }

    if(selectedNode == this) {
        selectedFlag = ImGuiTreeNodeFlags_Selected;
    } else {
        selectedFlag = ImGuiTreeNodeFlags_None;
    }
}
