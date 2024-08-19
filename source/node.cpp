#include <node.hpp>

#include <scene.hpp>

node::node(scene* ownerScene, node* parent, const char* name) : m_ownerScene(ownerScene), m_name(name), m_ID(m_ownerScene->newID()), m_parent(parent) {
}

std::string node::save() {
    std::string saveData;

    

    for(size_t i = 0; i < m_children.size(); i++) {
        saveData += m_children.at(i).save();
    }

    return saveData;
}
