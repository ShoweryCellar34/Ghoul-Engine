#pragma once

#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include <defines.hpp>

typedef size_t nodeID;

struct node {
private:
    nodeRef m_root;
    nodeRef m_parent;
    std::string m_data;
    std::string m_name;
    std::vector<nodeRef> m_children;

public:
    node(nodeRef root, nodeRef parent, const char* data, const char* name);

    void setName(const char* name);
    void addChild(const char* name);
    void reparent(nodeRef newParent);

    const char* getName() const;
    nodeRef getChild(const char* name) const;
    nodeRef getParent() const;

    nlohmann::json getJSON() const;
};
