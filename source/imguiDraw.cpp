#include <imguiDraw.hpp>

#include <string>
#include <format>
#include <tinyfiledialogs.h>
#include <imgui.h>
#include <Pentagram.hpp>
#include <defines_and_globals.hpp>
#include <fileInterfaces.hpp>
#include <node.hpp>

namespace GH {
    RENAME_STATUS drawRenameWindow(std::string& output, const std::string& title) {
        const char* result = tinyfd_inputBox(title.c_str(), nullptr, "");

        if(result == nullptr) {
            return RENAME_STATUS::CANCLED;
        }

        output = result;
        return RENAME_STATUS::SUCCESS;
    }

    RENAME_STATUS drawRenameWindow(void(*output)(std::string), std::string title) {
        const char* result = tinyfd_inputBox(title.c_str(), nullptr, "");

        if(result == nullptr) {
            return RENAME_STATUS::CANCLED;
        }

        output(result);
        return RENAME_STATUS::SUCCESS;
    }

    void drawGlobalDockingWindow() {
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
    }

    void drawMainMenuBar() {
        ImGui::BeginMainMenuBar();

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
            if(ImGui::MenuItem("Exit", "ALT+F4")) {
                g_window.setShouldClose(true);
            }

            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Edit")) {
            if(ImGui::MenuItem("Copy")) {
                copyNode();
            }
            if(ImGui::MenuItem("Cut")) {
                cutNode();
            }
            if(ImGui::MenuItem("Paste")) {
                pasteNode();
            }
            if(ImGui::MenuItem("Rename Project")) {
                if(drawRenameWindow(g_projectName, "Rename Project") == RENAME_STATUS::SUCCESS) {
                    refreshTitle();
                }
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    void drawScenePopup(const nodeRef node) {
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
                if(drawRenameWindow(node->m_name, "Rename Scene") == RENAME_STATUS::SUCCESS) {
                    ImGui::CloseCurrentPopup();
                }
            }
            ImGui::EndPopup();
        }
    }

    void drawNodeTree() {
        if(g_currentScene == nullptr) {
            return;
        }

        ImGui::SetNextWindowSize(ImVec2(265, g_window.getHeight() - 21), ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(g_window.getXPos() + g_window.getWidth() - 265, g_window.getYPos() + 21), ImGuiCond_Once);
        ImGui::Begin(g_currentScene->getName().c_str(), nullptr);

        for(nodeRef child : g_currentScene->m_children) {
            child->imguiDraw();
        }

        if(ImGui::IsWindowHovered() && ImGui::IsMouseClicked(1) && !ImGui::IsAnyItemHovered()) {
            ImGui::OpenPopup("Window right-click popup");
        }
        drawScenePopup(g_currentScene);

        if(ImGui::IsWindowHovered() && ImGui::IsMouseClicked(0) && !ImGui::IsAnyItemHovered()) {
            g_currentScene->selectNode(nullptr);
        }

        ImGui::End();
    }

    void drawNodeInspector() {
        ImGui::SetNextWindowSize(ImVec2(265, g_window.getHeight() - 21), ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(g_window.getXPos() + 0, g_window.getYPos() + 21), ImGuiCond_Once);
        ImGui::Begin("Node Inspector", nullptr);

        if(g_currentScene->getSelectedNode() != nullptr) {
            ImGui::Text("Name: %s", g_currentScene->getSelectedNode()->getName().c_str());
            ImGui::SameLine(235);
            if(ImGui::ImageButton(newFrameIDstr().c_str(), UITextureIDs::edit, ImVec2(16, 16))) {
                g_currentScene->getSelectedNode()->renameGUI();
            }

            ImGui::Text("ImGui name: %s", g_currentScene->getSelectedNode()->getImGuiName().c_str());

        } else {
            ImGui::TextWrapped("Select a node in the node tree panel.");
        }

        ImGui::End();
    }
}
