#include <node.hpp>

node::node(nodeRef root, nodeRef parent, const char* data, const char* name)
     : m_root(root), m_parent(parent), m_data(data), m_name(name) {}

void node::setName(const char* name) {
    m_name = name;
}

void node::addChild(const char *name) {
    m_children.push_back(std::make_shared<node>(m_root, (nodeRef)this, "", name));
}

void node::reparent(nodeRef newParent) {
    m_parent = newParent;
    newParent.get()->m_children.push_back((nodeRef)this);
    m_children.erase(std::find(m_children.begin(), m_children.end(), (nodeRef)this));
}

const char* node::getName() const {
    return m_name.c_str();
}

nodeRef node::getChild(const char* name) const {
    nodeRef result = nullptr;
    for(nodeRef child : m_children) {
        if(child.get()->m_name == name) {
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
        children["children"].push_back(child.get()->getJSON());
    }
    json["children"] = children;
    
    return json;
}
