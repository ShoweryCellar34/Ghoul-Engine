#include <imguiDraw.hpp>

#include <imgui.h>
#include <Pentagram.hpp>
#include <node.hpp>

void drawGlobalDockingWindow(const PNT::Window& window) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2(window.getWidth(), window.getHeight()));
    ImGui::SetNextWindowPos(ImVec2(window.getXPos(), window.getYPos()));
    ImGui::Begin("Tool Docking Area", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus |
                                                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing |
                                                ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
    ImGui::DockSpace(ImGui::GetID("MyDockSpace"), ImVec2(window.getWidth(), window.getHeight()));
    ImGui::End();
    ImGui::PopStyleVar(2);
}

void drawNodeTree(const PNT::Window& window, const node &node) {
    ImGui::SetNextWindowSize(ImVec2(265, window.getHeight()), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(window.getXPos() + window.getWidth() - 265, window.getYPos()), ImGuiCond_Once);
    ImGui::Begin("Node Tree", nullptr);

    node.ImGuiDraw();

    ImGui::End();
}

void drawNodeInspector(const PNT::Window& window) {
    ImGui::SetNextWindowSize(ImVec2(265, window.getHeight()), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(window.getXPos() + 0, window.getYPos()), ImGuiCond_Once);
    ImGui::Begin("Node Inspector", nullptr);

    if(node::selectedNode != nullptr) {
        ImGui::Text("Selected node name: %s", node::selectedNode->getName());
        ImGui::Text("Selected node ID: %lu", node::selectedNode->getID());
        ImGui::Text("Path: %s", node::selectedNode->getPath().c_str());
    }

    ImGui::End();
}
