#pragma once

#include <string>
#include <vector>

typedef size_t nodeID;

struct node {
private:
    std::string m_name;
    nodeID m_ID;
    std::vector<node> m_children;
    node* m_parent;

public:
    node(const char* name);
    ~node();

    void setName(const char* name);
    void setName(std::string name);
    void addChild(const char* name);
    void addChild(std::string name);
    void addChild();
    void reparent(nodeID newParent);

    const char* getName() const;
    nodeID getChild(const char* name) const;
    nodeID getChild(std::string name) const;
    nodeID getParent() const;
    nodeID getID() const;
};
