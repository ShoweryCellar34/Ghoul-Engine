#pragma once

#include <string>
#include <vector>

typedef size_t nodeID;
struct scene;

struct node {
private:
    scene* m_ownerScene;
    std::string m_name;
    nodeID m_ID;
    std::vector<node> m_children;
    node* m_parent;

public:
    node(scene* ownerScene, node* parent, const char* name);
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

    void load(std::string saveData);
    std::string save();
};
