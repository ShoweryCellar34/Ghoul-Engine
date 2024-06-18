#include <Pentagram.hpp>

void eventCallback(PNT::Window *window, PNT::windowEvent event) {
}

int main(int argc, char *argv[]) {
    PNT::init();

    PNT::Window window("Ghoul Engine", 1000, 700, 200, 200, ImGuiConfigFlags_ViewportsEnable | ImGuiConfigFlags_DockingEnable);
    window.setEventCallback(&eventCallback);
    window.setClearColor(0.25f, 0.25f, 0.25f, 0.25f);

    // Set icon.
    PNT::image icon("res\\textures\\logo\\ghoul32x32.png", 4);
    window.setIcon(icon);

    while(!window.shouldClose()) {
        PNT::processEvents();

        window.startFrame();

        ImGui::Begin("Controls");
        ImGui::End();

        window.endFrame();
    }

    PNT::deinit();
    return 0;
}
