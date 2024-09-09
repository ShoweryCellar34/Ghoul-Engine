#include <Pentagram.hpp>

#include <iostream>
#include <memory>
#include <node.hpp>
#include <imguiDraw.hpp>
#include <defines_and_globals.hpp>

void eventCallback(PNT::Window* window, PNT::windowEvent event) {
    switch(event.type) {
    case PNT_EVENT_TYPE_KEYBOARD:
        switch(event.keyboard.key) {
        case GLFW_KEY_S:
            if(event.keyboard.mods == GLFW_MOD_CONTROL && event.keyboard.action == GLFW_RELEASE) {
                nodeRef node = reinterpret_cast<nodeRef>(window->getUserPointer());
                std::string input;
                std::string filename = "a";
                std::cin >> input;
                nlohmann::json json;
                try {
                    json = nlohmann::json::parse(input);
                    node->loadJSON(json);
                } catch(const nlohmann::json::exception& exeption) {
                    userLogger.get()->error("Failed to parse file \"{}\": {}", filename, exeption.what());
                }
            }
            break;
        }
        break;
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
    window.setClearColor(0.33f, 0.33f, 0.33f, 1.0f);

    nodeRef world = new node(nullptr, nullptr, "", "ROOT");
    window.setUserPointer(world);

    while(!window.shouldClose()) {
        PNT::processEvents();
        window.startFrame();

        drawGlobalDockingWindow(window);
        drawMainMenuBar();
        drawNodeTree(window, world);
        drawNodeInspector(window, world);

        window.endFrame();
    }

    delete world;

    PNT::deinit();
    return 0;
}
