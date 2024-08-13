#include <node.hpp>

#include <cstring>
#include <string>
#include <algorithm>
#include <imgui.h>
#include <scene.hpp>

// node::node(scene* scene, size_t nodeParent, size_t nodeID, const char* name) : selectedFlag(ImGuiTreeNodeFlags_None), ID(nodeID), name(nullptr), imguiName(nullptr), parent(nodeParent), shouldOpen(false) {
//     setName(name);
// }

// node::node(scene* scene, size_t nodeParent, size_t nodeID) : selectedFlag(ImGuiTreeNodeFlags_None), ID(nodeID), name(nullptr), imguiName(nullptr), parent(nodeParent), shouldOpen(false) {
//     setName("Unnamed");
// }

// node::~node() {
//     parent->children.erase(std::find(parent->children.begin(), parent->children.end(), this));
//     delete[] name;
//     delete[] imguiName;
//     for(node* node : children) {
//         parentScene->deleteNode(node->getID());
//     }
// }

// node* node::addChild(const char* name) {
//     size_t child = parentScene->newNode(ID, name);
//     children.push_back(parentScene->getNode(child));
//     return parentScene->getNode(child);
// }

// node* node::addChild() {
//     size_t child = parentScene->newNode(ID, "Unnamed");
//     children.push_back(parentScene->getNode(child));
//     return parentScene->getNode(child);
// }

// bool node::deleteChild(const char* name) {
//     for(node* node : children) {
//         if(node->getName() == name) {
//             parentScene->deleteNode(node->getID());
//             return true;
//         }
//     }
//     return false;
// }

// bool node::deleteChild(size_t ID) {
//     for(node* node : children) {
//         if(node->getID() == ID) {
//             parentScene->deleteNode(node->getID());
//             return true;
//         }
//     }
//     return false;
// }

// void node::setName(const char *name) {
//     if(name != this->name) {
//         if(this->name != nullptr) {
//             delete[] this->name;
//         }
//         if(strlen(name) > 0) {
//             this->name = new char[strlen(name) + 1];
//             strcpy(this->name, name);
//         } else {
//             this->name = new char[1];
//             this->name[0] = 0;
//         }

//         if(this->imguiName != nullptr) {
//             delete[] imguiName;
//         }
//         imguiName = new char[strlen(this->name) + 2 + strlen(std::to_string(ID).c_str()) + 1];
//         strcpy(imguiName, this->name);
//         strcat(imguiName, "##");
//         strcat(imguiName, std::to_string(ID).c_str());
//     }
// }

// node* node::reparent(size_t ID) {
//     return nullptr;
// }

// std::vector<node*> node::getChildren() const {
//     return children;
// }

// node* node::getChild(const char* name) const {
//     for(node* node : children) {
//         if(node->getName() == name) {
//             return node;
//         }
//     }
//     return nullptr;
// }

// node* node::getChild(size_t ID) const {
//     for(node* node : children) {
//         if(node->getID() == ID) {
//             return node;
//         }
//     }
//     return nullptr;
// }

// const char* node::getName() const {
//     return name;
// }

// size_t node::getID() const {
//     return ID;
// }

// node* node::getParent() const {
//     return parent;
// }

// void drawPopup(node* node) {
//     if(ImGui::Button("Add child")) {
//         node->addChild();
//         node->shouldOpen = true;
//         ImGui::CloseCurrentPopup();
//     }
//     if(ImGui::Button("Remove")) {
//         delete node;
//         ImGui::CloseCurrentPopup();
//     }
// }

// void node::ImGuiDraw() const {
//     ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | selectedFlag;
//     if(children.size() == 0) {
//         flags |= ImGuiTreeNodeFlags_Leaf;
//     }
//     if(shouldOpen) {
//         ImGui::SetNextItemOpen(true);
//         shouldOpen = false;
//     }
//     if(ImGui::TreeNodeEx(imguiName, flags)) {
//         if(ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
//             parentScene->selectID(ID);
//         }
//         if(ImGui::BeginPopupContextItem()) {
//             drawPopup((node*)this);
//             ImGui::EndPopup();
//         }

//         for(node* child : children) {
//             child->ImGuiDraw();
//         }
//         ImGui::TreePop();
//     } else {
//         if(ImGui::BeginPopupContextItem()) {
//             drawPopup((node*)this);
//             ImGui::EndPopup();
//         }
//     }

//     if(parentScene->getSelectedID() == ID) {
//         selectedFlag = ImGuiTreeNodeFlags_Selected;
//     } else {
//         selectedFlag = ImGuiTreeNodeFlags_None;
//     }
// }

node::node(scene* ownerScene, nodeID parent, nodeID ID, const char* name) : m_ParentScene(ownerScene), m_Parent(parent), m_ID(ID), m_Name(nullptr), m_ImguiName(nullptr) {
    setName(name);
}

void node::setName(const char *name) {
    if(name != this->m_Name) {
        if(this->m_Name != nullptr) {
            delete[] this->m_Name;
        }
        if(strlen(name) > 0) {
            this->m_Name = new char[strlen(name) + 1];
            strcpy(this->m_Name, name);
        } else {
            this->m_Name = new char[1];
            this->m_Name[0] = 0;
        }

        if(this->m_ImguiName != nullptr) {
            delete[] m_ImguiName;
        }
        m_ImguiName = new char[strlen(this->m_Name) + 2 + strlen(std::to_string(m_ID).c_str()) + 1];
        strcpy(m_ImguiName, this->m_Name);
        strcat(m_ImguiName, "##");
        strcat(m_ImguiName, std::to_string(m_ID).c_str());
    }
}

node::~node() {
    for(nodeID child : children) {
        m_ParentScene->deleteNode(child);
    }
}

void node::reparent(nodeID newParent) {
    m_ParentScene->getNode(newParent)->children.push_back(newParent);
    m_ParentScene->getNode(m_Parent)->children.erase(std::find(m_ParentScene->getNode(m_Parent)->children.begin(), m_ParentScene->getNode(m_Parent)->children.end(), m_ID));
    m_Parent = newParent;
}

nodeID node::addChild(const char *name) {
    nodeID child = m_ParentScene->newNode(m_ID, name);
    children.push_back(child);
    return child;
}

nodeID node::getParent() const {
    return m_Parent;
}

nodeID node::getID() const
{
    return m_ID;
}

void drawPopup(node* node) {
    if(ImGui::BeginPopupContextItem()) {
        if(ImGui::Button("Add child")) {
            node->addChild("Unnamed child");
            node->m_ShouldOpen = true;
            ImGui::CloseCurrentPopup();
        }
        if(ImGui::Button("Remove")) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void node::ImDraw() const {
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | m_SelectedFlag;
    if(children.size() == 0) {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }
    if(m_ShouldOpen) {
        ImGui::SetNextItemOpen(true);
        m_ShouldOpen = false;
    }
    if(ImGui::TreeNodeEx(m_ImguiName, flags)) {
        if(ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
            m_ParentScene->selectID(m_ID);
        }
        drawPopup((node*)this);

        for(nodeID child : children) {
            m_ParentScene->getNode(child)->ImDraw();
        }
        ImGui::TreePop();
    } else {
        drawPopup((node*)this);
    }

    if(m_ParentScene->getSelectedID() == m_ID) {
        m_SelectedFlag = ImGuiTreeNodeFlags_Selected;
    } else {
        m_SelectedFlag = ImGuiTreeNodeFlags_None;
    }
}
