#include <imguiDraw.hpp>

#include <imgui.h>
#include <Pentagram.hpp>
#include <fileInterfaces.hpp>
#include <node.hpp>

int drawRenameWindow(bool* renaming, std::string* output, std::string* buffer, std::string title) {
    ImGui::SetNextWindowSize(ImVec2(200, 54));
    ImGui::SetNextWindowPos(ImVec2((g_window.getXPos() + g_window.getWidth() / 2) - 100, (g_window.getYPos() + g_window.getHeight() / 2) - 27));
    ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    ImGui::InputText((("##" + std::to_string((std::uintptr_t)buffer))).c_str(), buffer);
    ImGui::SetKeyboardFocusHere();
    ImGui::End();
    if(ImGui::IsKeyDown(ImGuiKey_Enter)) {
        *output = *buffer;
        *renaming = false;
        return 2;
    } else if(ImGui::IsKeyDown(ImGuiKey_Escape)) {
        *renaming = false;
        return 1;
    }
    return 0;
}

int drawRenameWindow(bool* renaming, void(*output)(std::string), std::string* buffer, std::string title) {
    ImGui::SetNextWindowSize(ImVec2(200, 54));
    ImGui::SetNextWindowPos(ImVec2((g_window.getXPos() + g_window.getWidth() / 2) - 100, (g_window.getYPos() + g_window.getHeight() / 2) - 27));
    ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    ImGui::InputText((("##" + std::to_string((std::uintptr_t)buffer))).c_str(), buffer);
    ImGui::SetKeyboardFocusHere();
    ImGui::End();
    if(ImGui::IsKeyDown(ImGuiKey_Enter)) {
        output(*buffer);
        *renaming = false;
        return 2;
    } else if(ImGui::IsKeyDown(ImGuiKey_Escape)) {
        *renaming = false;
        return 1;
    }
    return 0;
}

void drawGlobalDockingWindow() {
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
}

void drawMainMenuBar() {
    ImGui::BeginMainMenuBar();

    static bool renaming = false;
    static std::string newName;

    if(ImGui::BeginMenu("File")) {
        if(ImGui::MenuItem("Save", "CTRL+S")) {
            saveScene();
        }

        if(ImGui::MenuItem("Save As", "CTRL+SHIFT+S")) {
            saveAs();
        }

        if(ImGui::MenuItem("Open", "CTRL+O")) {
            loadProject();
        }

        ImGui::EndMenu();
    }

    if(ImGui::BeginMenu("Edit")) {
        if(ImGui::MenuItem("Copy")) {
            g_nodeClipboard = g_currentScene->getSelectedNode()->getJSON();
        }
        if(ImGui::MenuItem("Cut")) {
            nodeRef selectedNode = g_currentScene->getSelectedNode();
            g_nodeClipboard = selectedNode->getJSON();
            selectedNode->removeSelf();
        }
        if(ImGui::MenuItem("Paste")) {
            g_currentScene->getSelectedNode()->addChild(g_nodeClipboard);
            g_currentScene->getSelectedNode()->m_shouldOpen = true;
        }
        if(ImGui::MenuItem("Rename Project")) {
            renaming = true;
            newName = g_projectName;
        }

        ImGui::EndMenu();
    }

    if(renaming) {
        if(drawRenameWindow(&renaming, &g_projectName, &newName, "Rename Project") == 2) {
            refreshTitle();
        }
    }

    ImGui::EndMainMenuBar();
}

void drawScenePopup(const nodeRef node) {
    static bool renaming = false;
    static std::string newName;
    if(!renaming) {
        if(ImGui::BeginPopup("Window right-click popup")) {
            if(ImGui::Button("Add node")) {
                nodeRef child = node->addChild((std::string)"node");
                node->m_root->selectNode(child);
                node->m_shouldOpen = true;
                ImGui::CloseCurrentPopup();
            }
            if(ImGui::Button("Paste")) {
                if(!g_nodeClipboard.empty()) {
                    nodeRef child = node->addChild(g_nodeClipboard);
                    node->m_root->selectNode(child);
                    node->m_shouldOpen = true;
                }
                ImGui::CloseCurrentPopup();
            }
            if(ImGui::Button("Rename scene")) {
                renaming = true;
                newName = node->getName();
            }
            ImGui::EndPopup();
        }
    } else {
        if(drawRenameWindow(&renaming, &node->m_name, &newName, "Rename Scene")) {
            ImGui::CloseCurrentPopup();
        }
    }
}

void drawNodeTree(const nodeRef nodeToDraw) {
    if(nodeToDraw == nullptr) {
        return;
    }

    ImGui::SetNextWindowSize(ImVec2(265, g_window.getHeight() - 17), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(g_window.getXPos() + g_window.getWidth() - 265, g_window.getYPos() + 17), ImGuiCond_Once);
    ImGui::Begin(nodeToDraw->getName().c_str(), nullptr);

    for(nodeRef child : nodeToDraw->m_children) {
        child->imguiDraw();
    }

    if(ImGui::IsWindowHovered() && ImGui::IsMouseClicked(1) && !ImGui::IsAnyItemHovered()) {
        ImGui::OpenPopup("Window right-click popup");
    }
    drawScenePopup(nodeToDraw);

    ImGui::End();
}

void drawNodeInspector(const nodeRef nodeToInspect) {
    if(nodeToInspect == nullptr) {
        return;
    }

    ImGui::SetNextWindowSize(ImVec2(265, g_window.getHeight() - 17), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(g_window.getXPos() + 0, g_window.getYPos() + 17), ImGuiCond_Once);
    ImGui::Begin("Node Inspector", nullptr);

    // Draw details

    ImGui::End();
}
