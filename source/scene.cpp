#include <scene.hpp>

nodeID scene::newID() {
    return m_IDCounter++;
}
