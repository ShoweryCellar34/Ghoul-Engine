#include <Pentagram.hpp>
#include <depracated/file.hpp>

#include <vector>
#include <node.hpp>

void eventCallback(PNT::Window* window, PNT::windowEvent event) {
    switch(event.type) {
    }
}

int main(int argc, char *argv[]) {
    stbi_set_flip_vertically_on_load(true);

    if(!PNT::init()) {
        exit(EXIT_FAILURE);
    }

    PNT::Window window("Ghoul Engine", 1200, 675, 250, 250, ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable);
    window.setAspectRatio(16, 9);
    window.setEventCallback(eventCallback);

    node* currentWorld = new node(nullptr, "World");

    while(!window.shouldClose()) {
        PNT::processEvents();
        window.startFrame();

        ImGui::SetNextWindowSize(ImVec2(265, window.getHeight()), ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(window.getXPos() + window.getWidth() - 265, window.getYPos()), ImGuiCond_Once);
        ImGui::Begin("Node Tree", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

        currentWorld->ImGuiDraw();

        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(265, window.getHeight()), ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(window.getXPos() + 0, window.getYPos()), ImGuiCond_Once);
        ImGui::Begin("Node Inspector", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);



        ImGui::End();

        window.endFrame();
    }

    delete currentWorld;

    PNT::deinit();
    return 0;
}
