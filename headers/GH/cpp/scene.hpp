#pragma once

#include <unordered_map>
#include <string>

namespace GH::scene::internal {
    class node {
    private:
        std::unordered_map<std::string, node*> m_children;
        node* m_parent;

    public:
    }
}
