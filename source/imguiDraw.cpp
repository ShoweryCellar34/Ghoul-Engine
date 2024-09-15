#include <imguiDraw.hpp>

#include <imgui.h>
#include <Pentagram.hpp>
#include <fileInterfaces.hpp>
#include <node.hpp>

void drawGlobalDockingWindow() {
    ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
}

void drawMainMenuBar() {
    ImGui::BeginMainMenuBar();

    if(ImGui::BeginMenu("File")) {
        if(ImGui::MenuItem("Save", "CTRL+S")) {
            saveScene((nodeRef)g_window.getUserPointer());
        }

        if(ImGui::MenuItem("Save As", "CTRL+SHIFT+S")) {
            saveAsNode((nodeRef)g_window.getUserPointer());
        }

        if(ImGui::MenuItem("Open", "CTRL+O")) {
            loadProject((nodeRef)g_window.getUserPointer());
        }

        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
}

void drawScenePopup(const nodeRef node) {
    static bool renaming = false;
    static std::string newName;
    if(!renaming) {
        if(ImGui::Button("Add node")) {
            nodeRef child = node->addChild(("node " + std::to_string(node->m_children.size())).c_str());
            node->m_root->selectNode(child);
            node->m_shouldOpen = true;
            ImGui::CloseCurrentPopup();
        }
        if(ImGui::Button("Rename scene")) {
            renaming = true;
            newName = node->getName();
        }
    } else {
        ImGui::Text("New name: ");
        ImGui::SameLine();
        ImGui::InputText(("##" + std::to_string((std::uintptr_t)node)).c_str(), &newName);
        if(ImGui::IsKeyDown(ImGuiKey_Enter)) {
            node->setName(newName.c_str());
            renaming = false;
            ImGui::CloseCurrentPopup();
        } else if(ImGui::IsKeyDown(ImGuiKey_Escape)) {
            renaming = false;
            ImGui::CloseCurrentPopup();
        }
    }
}

void drawNodeTree(const nodeRef nodeToDraw) {
    ImGui::SetNextWindowSize(ImVec2(265, g_window.getHeight() - 17), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(g_window.getXPos() + g_window.getWidth() - 265, g_window.getYPos() + 17), ImGuiCond_Once);
    ImGui::Begin(nodeToDraw->getName(), nullptr);

    for(nodeRef child : nodeToDraw->m_children) {
        child->imguiDraw();
    }

    if(ImGui::IsWindowHovered() && ImGui::IsMouseClicked(1) && !ImGui::IsAnyItemHovered()) {
        ImGui::OpenPopup("Window right-click popup");
    }
    if(ImGui::BeginPopup("Window right-click popup")) {
        drawScenePopup(nodeToDraw);
        ImGui::EndPopup();
    }

    ImGui::End();
}

void drawNodeInspector(const nodeRef nodeToInspect) {
    ImGui::SetNextWindowSize(ImVec2(265, g_window.getHeight() - 17), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(g_window.getXPos() + 0, g_window.getYPos() + 17), ImGuiCond_Once);
    ImGui::Begin("Node Inspector", nullptr);

    // Draw details

    ImGui::End();
}
