#include <Pentagram.hpp>

void eventCallback(PNT::Window *window, PNT::windowEvent event) {
}

void startFrameCallback(PNT::Window *window) {
    ImGui::Begin("Controls");
    ImGui::End();
}

int main(int argc, char *argv[]) {
    PNT::init();

    PNT::Window window("Ghoul Engine", 1000, 700, 200, 200, ImGuiConfigFlags_ViewportsEnable | ImGuiConfigFlags_DockingEnable);
    window.setCallback(PNT_CALLBACK_FLAGS_STARTFRAME, &startFrameCallback);
    window.setEventCallback(&eventCallback);
    window.setClearColor(0.25f, 0.25f, 0.25f, 0.25f);
    PNT::image icon("..\\ghoul.png", 4);
    icon.resize(32, 32);
    window.setIcon(icon);
    icon.loadOnGPU();

    while(!window.shouldClose()) {
        PNT::processEvents();

        window.startFrame();
        icon.ImGuiDraw();
        window.endFrame();
    }

    PNT::deinit();
    return 0;
}
