#include <GH/cpp/scene.hpp>

#include <GH/cpp/error.hpp>

namespace GH::scene::internal {
    // Node definitions

    node::node(node* parent) : m_parent(parent) {
        if(m_parent == nullptr) {
            m_isRoot = true;
            m_root = this;
        } else {
            m_isRoot = false;
            m_root = m_parent->getRoot();
        }
    }

    node::node(node* parent, nlohmann::json data) : m_parent(parent) {
        if(m_parent == nullptr) {
            m_isRoot = true;
            m_root = this;
        } else {
            m_isRoot = false;
            m_root = m_parent->getRoot();
        }

        setJSON(data);
    }

    void node::addChild(const std::string& name) {
        if(m_children.find(name) != m_children.end()) {
            if(m_isRoot) {
                throw error::exception("Node name \"" + name + "\" is an in use child name for root node.");
            } else {
                throw error::exception("Node name \"" + name + "\" is an in use child name for node \"" + m_parent->getChildName(this) + "\".");
            }
        }

        m_children.insert({name, node(this)});
    }

    void node::addChild(const std::string& name, nlohmann::json data) {
        if(m_children.find(name) != m_children.end()) {
            if(m_isRoot) {
                throw error::exception("Node name \"" + name + "\" is an in use child name for root node.");
            } else {
                throw error::exception("Node name \"" + name + "\" is an in use child name for node \"" + m_parent->getChildName(this) + "\".");
            }
        }

        m_children.insert({name, node(this, data)});
    }

    void node::deleteChild(const std::string& name) {
        if(m_children.find(name) == m_children.end()) {
            if(m_isRoot) {
                throw error::exception("Node name \"" + name + "\" is not an in use child name for root node.");
            } else {
                throw error::exception("Node name \"" + name + "\" is not an in use child name for node \"" + m_parent->getChildName(this) + "\".");
            }
        }

        m_children.erase(name);
    }

    void node::setChildren(const std::unordered_map<std::string, node>& children) {
        m_children.clear();
        m_children = children;

        for(const std::pair<std::string, node>& child : m_children) {
            node& node = m_children.at(child.first);
            node.m_isRoot = false;
            node.m_parent = this;
            node.m_root = m_root;
        }
    }

    void node::setParent(node* parent) {
        if(m_isRoot) {
            throw error::exception("Cannot reparent root node");
        }

        parent->addChild(m_parent->getChildName(this), getJSON());
        m_parent->deleteChild(m_parent->getChildName(this));
    }

    void node::setData(const nlohmann::json& data) {
        m_data = data;
    }

    node& node::getChild(const std::string& name) const {
        if(m_children.find(name) == m_children.end()) {
            if(m_isRoot) {
                throw error::exception("Node name \"" + name + "\" is not an in use child name for root node.");
            } else {
                throw error::exception("Node name \"" + name + "\" is not an in use child name for node \"" + m_parent->getChildName((node*)this) + "\".");
            }
        }

        return (node&)m_children.at(name);
    }

    std::string node::getChildName(node* target) const {
        node* found = nullptr;
        std::string result;
        for(const std::pair<std::string, node>& child : m_children) {
            if(&child.second == target) {
                result = child.first;
            }
        }

        if(found == nullptr) {
            if(m_isRoot) {
                throw error::exception("Target node not a child of root node.");
            } else {
                throw error::exception("Target node not a child of node with name \"" + m_parent->getChildName((node*)this) + "\".");
            }
        }

        return result;
    }

    std::unordered_map<std::string, node*> node::getChildren() const {
        std::unordered_map<std::string, node*> result;

        for(const std::pair<std::string, node>& child : m_children) {
            result.insert({child.first, (node*)&child.second});
        }

        return result;
    }

    node* node::getParent() const {
        return m_parent;
    }

    node* node::getRoot() const {
        return m_root;
    }

    bool node::getIsRoot() const {
        return m_isRoot;
    }

    nlohmann::json node::getData() const {
        return m_data;
    }

    void node::setJSON(const nlohmann::json& data) {
    }

    nlohmann::json node::getJSON() const {
    }
}
