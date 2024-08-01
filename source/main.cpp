#include <Pentagram.hpp>
#include <depracated/file.hpp>

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

    node test(nullptr);
    for (size_t i = 0; i < 10; i++) {
        test.addChild(std::to_string(i).c_str());
    }
    

    while(!window.shouldClose()) {
        PNT::processEvents();

        window.startFrame();

        test.ImGuiDraw();

        window.endFrame();
    }

    PNT::deinit();
    return 0;
}
