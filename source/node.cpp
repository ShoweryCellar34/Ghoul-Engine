#include <node.hpp>

nlohmann::json node::getJSON() const {
    nlohmann::json json;
    json["name"] = m_name;
    json["data"] = m_data;

    nlohmann::json children = nlohmann::json::array();
    for() {
        children["children"].push_back(child.get()->getJSON());
    }
    json["children"] = children;
    
    return json;
}

node::node(std::shared_ptr<node> root, std::shared_ptr<node> parent, const char* data, const char* name)
     : m_root(root), m_parent(parent), m_data(data), m_name(name) {}

void node::setName(const char* name) {
    m_name = name;
}

void node::addChild(const char *name) {
    //m_children.push_back(std::make_shared<node>(m_root, this, "", name));
}

void node::addChild() {
    //m_children.push_back(std::make_shared<node>(m_root, this, "", "child " + std::to_string(m_children.size())));
}
