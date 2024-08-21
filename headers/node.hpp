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
    std::string m_name;
    nodeID m_ID;
    std::vector<std::shared_ptr<node>> m_children;
    std::shared_ptr<node> m_parent;
    std::string m_data;

public:
    node(std::shared_ptr<node> root, std::shared_ptr<node> parent, std::string data, std::string name);
    ~node();

    void setName(const char* name);
    void setName(std::string name);
    void addChild(const char* name);
    void addChild(std::string name);
    void addChild();
    void reparent(node* newParent);

    const char* getName() const;
    node* getChild(const char* name) const;
    node* getChild(std::string name) const;
    node* getParent() const;
    node* getID() const;

    nlohmann::json getJSON() const;
};
