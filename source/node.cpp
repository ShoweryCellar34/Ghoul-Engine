#include <node.hpp>

#include <scene.hpp>

node::node(const char* name) : m_name(name), m_ID(m_OwnerScene->newID()) {
}
