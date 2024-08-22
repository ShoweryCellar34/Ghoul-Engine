#pragma once

#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>

typedef size_t nodeID;
struct scene;

struct node {
private:
    std::shared_ptr<node> m_root;
    std::shared_ptr<node> m_parent;
    std::string m_data;
    std::string m_name;
    std::vector<node> m_children;

public:
    node(std::shared_ptr<node> root, std::shared_ptr<node> parent, const char* data, const char* name);

    void setName(const char* name);
    void addChild(const char* name);
    void addChild();
    void reparent(std::shared_ptr<node> newParent);

    const char* getName() const;
    std::shared_ptr<node> getChild(const char* name) const;
    std::shared_ptr<node> getParent() const;

    nlohmann::json getJSON() const;
};
