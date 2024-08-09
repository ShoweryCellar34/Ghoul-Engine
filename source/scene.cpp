#include <scene.hpp>

node *scene::newNode(node* parent, const char* name) {
    node* node = new node(this, parent, name, nodeIDCounter++);
    nodes.insert({nodeIDCounter, node});
    return node;
}
