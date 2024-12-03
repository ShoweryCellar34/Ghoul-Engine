#pragma once

#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>

namespace GH::scene::internal {
    class node {
    private:
        std::unordered_map<std::string, node> m_children;
        node* m_parent;
        node* m_root;
        bool m_isRoot;
        nlohmann::json m_data;

    public:
        node(node* parent);
        node(node* parent, nlohmann::json data);

        void addChild(const std::string& name);
        void addChild(const std::string& name, nlohmann::json data);
        void deleteChild(const std::string& name);
        void setChildren(const std::unordered_map<std::string, node>& children);
        void setParent(node* parent);
        void setData(const nlohmann::json& data);

        node& getChild(const std::string& name) const;
        std::string getChildName(node* target) const;
        std::unordered_map<std::string, node*> getChildren() const;
        node* getParent() const;
        node* getRoot() const;
        bool getIsRoot() const;
        nlohmann::json getData() const;

        void setJSON(const nlohmann::json& json);
        nlohmann::json getJSON() const;
    };
}
