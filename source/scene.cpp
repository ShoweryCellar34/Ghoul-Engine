#include <scene.hpp>

#include <cstring>
#include <string>
#include <node.hpp>

scene::scene(const char *name) : title(nullptr), selectedNode(0), nodeIDCounter(0) {
    setTitle(name);
}

scene::~scene() {
    delete[] title;
}

node* scene::newNode(node* parent, const char* name) {
    node* newNode = new node(this, parent, nodeIDCounter++, name);
    nodes.insert({nodeIDCounter, newNode});
    return newNode;
}

void scene::deleteNode(size_t ID) {
    delete nodes.at(ID);
    nodes.erase(ID);
}

void scene::selectID(size_t ID) {
    selectedNode = ID;
}

void scene::setTitle(const char* name) {
    if(name != this->title) {
        if(this->title != nullptr) {
            delete[] this->title;
        }
        if(strlen(name) > 0) {
            this->title = new char[strlen(name)];
            strcpy(this->title, name);
        } else {
            this->title = new char[1];
            this->title[0] = 0;
        }
    }
}

size_t scene::getSelectedID() {
    return selectedNode;
}

node* scene::getNode(size_t ID) {
    return nodes.at(ID);
}

const char* scene::getTitle() {
    return title;
}

std::vector<node*> scene::getChildren() {
    return std::vector<node*>();
}
