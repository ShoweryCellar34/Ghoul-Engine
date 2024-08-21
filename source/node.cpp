#include <node.hpp>

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

node::node(std::shared_ptr<node> root, std::shared_ptr<node> parent, std::string data, std::string name) {
}
