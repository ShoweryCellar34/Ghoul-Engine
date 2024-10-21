#include <defines_and_globals.hpp>

#include <Pentagram.hpp>
#include <node.hpp>
#include <resourceManager.hpp>
#include <texture.hpp>

namespace GH {
    void copyNode() {
        if(g_currentScene->getSelectedNode() == nullptr) {
            return;
        }
        g_nodeClipboard = g_currentScene->getSelectedNode()->getJSON();
    }

    void cutNode() {
        nodeRef selectedNode = g_currentScene->getSelectedNode();
        if(selectedNode == nullptr) {
            return;
        }
        g_nodeClipboard = selectedNode->getJSON();
        selectedNode->removeSelf();
    }

    void pasteNode() {
        if(g_nodeClipboard.empty()) {
            return;
        }
        nodeRef selectedNode = g_currentScene->getSelectedNode();
        if(selectedNode == nullptr) {
            selectedNode = g_currentScene;
        }
        selectedNode->addChild(g_nodeClipboard);
        selectedNode->m_shouldOpen = true;
    }

    void copyNode(nodeRef target) {
        g_nodeClipboard = g_currentScene->getSelectedNode()->getJSON();
    }

    void cutNode(nodeRef target) {
        g_nodeClipboard = target->getJSON();
        target->removeSelf();
    }

    void pasteNode(nodeRef target) {
        if(g_nodeClipboard.empty()) {
            return;
        }
        nodeRef child = target->addChild(g_nodeClipboard);
        target->m_shouldOpen = true;
        target->m_root->selectNode(child);
    }

    void refreshTitle() {
        std::string title;
        title += g_projectName + " | Ghoul Engine";

        g_window.setTitle(title);
    }

    ::size_t counter = 0;
    size_t newID() {
        return counter++;
    }

    std::string newIDstr() {
        return std::to_string(counter++);
    }

    ::size_t frameIDs = 0;
    size_t newFrameID() {
        return frameIDs++;
    }

    std::string newFrameIDstr() {
        return std::to_string(frameIDs++);
    }

    void clearFrameIDs() {
        frameIDs = 0;
    }

    void loadUITextures() {
        g_resourceManager.loadResource("editIcon", "./res/textures/UI/edit.png");
        std::string editIconData = g_resourceManager.getData("editIcon");
        g_UITextures[0].setGL(g_window.getGL());
        g_UITextures[0].setData(editIconData);
        g_UITextures[0].load();
        UITextureIDs::edit = g_UITextures[0].getID();
    }
}
