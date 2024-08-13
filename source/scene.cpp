#include <scene.hpp>

#include <cstring>
#include <string>
#include <imgui.h>
#include <node.hpp>

scene::scene(const char *name) : name(nullptr), selectedNode(0), nodeIDCounter(1) {
    setName(name);
}

scene::scene() : name(nullptr), selectedNode(0), nodeIDCounter(1) {
    setName("Unnamed scene");
}

scene::~scene() {
    delete[] name;
    for(nodeID ID = 1; ID < nodeIDCounter; ID++) {
        deleteNode(ID);
    }
}

nodeID scene::newNode(nodeID parent, const char* name) {
    node* newNode = new node(this, parent, nodeIDCounter++, name);
    nodes.insert({nodeIDCounter, newNode});
    return newNode->getID();
}

void scene::deleteNode(nodeID ID) {
    delete nodes.at(ID);
    nodes.erase(ID);
}

void scene::selectID(nodeID ID) {
    selectedNode = ID;
}

nodeID scene::getSelectedID() const {
    return selectedNode;
}

node* scene::getNode(nodeID ID) const {
    return nodes.at(ID);
}

void scene::setName(const char* title) {
    if(title != this->name) {
        if(this->name != nullptr) {
            delete[] this->name;
        }
        if(strlen(title) > 0) {
            this->name = new char[strlen(title) + 1];
            strcpy(this->name, title);
        } else {
            this->name = new char[1];
            this->name[0] = 0;
        }
    }
}

nodeID scene::addChild(const char* name) {
    nodeID child = newNode(0, name);
    children.push_back(child);
    return child;
}

bool scene::removeChild(nodeID ID) {
    if(children.erase(std::find(children.begin(), children.end(), ID)) == children.end()) {
        return false;
    }
    return true;
}

const char* scene::getName() const {
    return name;
}

std::vector<nodeID> scene::getChildren() const {
    return children;
}

void scene::ImDraw() const {
    for(nodeID child : children) {
        getNode(child)->ImDraw();
    }
}
