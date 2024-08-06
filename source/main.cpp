#include <Pentagram.hpp>
#include <depracated/file.hpp>

#include <vector>
#include <node.hpp>
#include <imguiDraw.hpp>

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

    node currentWorld(nullptr, "World");

    while(!window.shouldClose()) {
        PNT::processEvents();
        window.startFrame();

        drawGlobalDockingWindow(window);
        drawNodeTree(window, currentWorld);
        drawNodeInspector(window);

        window.endFrame();
    }

    PNT::deinit();
    return 0;
}
