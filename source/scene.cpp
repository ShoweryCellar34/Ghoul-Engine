#include <scene.hpp>

#include <cstring>
#include <string>
#include <node.hpp>

node* scene::newNode(node* parent, const char* name) {
    node* newNode = new node(this, parent, nodeIDCounter++, name);
    nodes.insert({nodeIDCounter, newNode});
    return newNode;
}

void scene::setName(const char* name) {
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
    }
}
