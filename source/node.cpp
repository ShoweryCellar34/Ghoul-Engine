#include <node.hpp>

node::node(std::shared_ptr<node> root, std::shared_ptr<node> parent, const char* data, const char* name)
     : m_root(root), m_parent(parent), m_data(data), m_name(name) {}

void node::setName(const char* name) {
    m_name = name;
}

void node::addChild(const char *name) {
    m_children.push_back(std::make_shared<node>(m_root, (std::shared_ptr<node>)this, "", name));
}

void node::reparent(std::shared_ptr<node> newParent) {
    m_parent = newParent;
    newParent.get()->m_children.push_back((std::shared_ptr<node>)this);
    m_children.erase(std::find(m_children.begin(), m_children.end(), (std::shared_ptr<node>)this));
}

const char* node::getName() const {
    return m_name.c_str();
}

std::shared_ptr<node> node::getChild(const char* name) const {
    std::shared_ptr<node> result = nullptr;
    for(std::shared_ptr<node> child : m_children) {
        if(child.get()->m_name == name) {
            result = child;
        }
    }
    return result;
}

std::shared_ptr<node> node::getParent() const {
    return m_parent;
}

nlohmann::json node::getJSON() const {
    nlohmann::json json;
    json["name"] = m_name;
    json["data"] = m_data;

    nlohmann::json children = nlohmann::json::array();
    for(std::shared_ptr<node> child : m_children) {
        children["children"].push_back(child.get()->getJSON());
    }
    json["children"] = children;
    
    return json;
}
