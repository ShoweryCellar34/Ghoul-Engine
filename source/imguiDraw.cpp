#include <imguiDraw.hpp>

#include <imgui.h>
#include <Pentagram.hpp>
#include <node.hpp>

void drawGlobalDockingWindow(const PNT::Window& window) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.0f);
    ImGui::SetNextWindowSize(ImVec2(window.getWidth(), window.getHeight()));
    ImGui::SetNextWindowPos(ImVec2(window.getXPos(), window.getYPos()));
    ImGui::Begin("Global docking are host window", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus |
                                                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing |
                                                ImGuiWindowFlags_NoMove);
    ImGui::DockSpace(ImGui::GetID("Global docking area"), ImVec2(window.getWidth(), window.getHeight()));
    ImGui::End();
    ImGui::PopStyleVar(3);
}

void drawScenePopup(nodeRef node) {
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

void drawNodeTree(const PNT::Window& window, nodeRef nodeToDraw) {
    ImGui::SetNextWindowSize(ImVec2(265, window.getHeight()), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(window.getXPos() + window.getWidth() - 265, window.getYPos()), ImGuiCond_Once);
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

void drawNodeInspector(const PNT::Window& window, nodeRef nodeToInspect) {
    ImGui::SetNextWindowSize(ImVec2(265, window.getHeight()), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(window.getXPos() + 0, window.getYPos()), ImGuiCond_Once);
    ImGui::Begin("Node Inspector", nullptr);

    // Draw details

    ImGui::End();
}
