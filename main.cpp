#include <PentagramHeaders/Pentagram.hpp>

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
    window.setIcon(PNT::image("..\\ghoul.png"));
    std::cout << stbi_failure_reason();

    while(!window.shouldClose()) {
        PNT::processEvents();

        window.startFrame();
        window.endFrame();
    }

    PNT::deinit();
    return 0;
}
