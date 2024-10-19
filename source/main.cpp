#include <string>
#include <vector>
#include <Pentagram.hpp>
#include <defines_and_globals.hpp>
#include <fileInterfaces.hpp>
#include <node.hpp>
#include <imguiDraw.hpp>
#include <resourceManager.hpp>
#include <texture.hpp>

void eventCallback(PNT::Window* window, PNT::windowEvent event) {
    switch(event.type) {
    case PNT_EVENT_TYPE_KEYBOARD:
        switch(event.keyboard.key) {
        case GLFW_KEY_S:
            if(event.keyboard.mods == GLFW_MOD_CONTROL + GLFW_MOD_SHIFT && event.keyboard.action == GLFW_RELEASE) {
                GH::saveAs();
            } else if(event.keyboard.mods == GLFW_MOD_CONTROL && event.keyboard.action == GLFW_RELEASE) {
                GH::saveScene();
            }
            break;

        case GLFW_KEY_O:
            if(event.keyboard.mods == GLFW_MOD_CONTROL && event.keyboard.action == GLFW_RELEASE) {
                GH::loadProject();
            }
            break;

        case GLFW_KEY_C:
            if(event.keyboard.mods == GLFW_MOD_CONTROL && event.keyboard.action == GLFW_RELEASE) {
                GH::copyNode();
            }
            break;

        case GLFW_KEY_X:
            if(event.keyboard.mods == GLFW_MOD_CONTROL && event.keyboard.action == GLFW_RELEASE) {
                GH::cutNode();
            }
            break;

        case GLFW_KEY_V:
            if(event.keyboard.mods == GLFW_MOD_CONTROL && event.keyboard.action == GLFW_RELEASE) {
                GH::pasteNode();
            }
            break;
        }
        break;
    }
}

int main(int argc, char* argv[]) {
    stbi_set_flip_vertically_on_load(false);

    if(!PNT::init()) {
        exit(EXIT_FAILURE);
    }

    GH::g_window.createWindow("Ghoul Engine", 1200, 675, 250, 250, ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable);
    GH::refreshTitle();
    GH::g_window.setEventCallback(eventCallback);
    GH::g_window.setClearColor(0.33f, 0.33f, 0.33f, 1.0f);

    GH::g_currentScene = new GH::node(nullptr, nullptr, "", "ROOT");
    GH::g_scenes.emplace_back(GH::g_currentScene);

    GH::g_window.startFrame();
    ImGui::GetFont()->Scale = 1.2f;
    GH::g_window.endFrame();
    GH::loadUITextures();

    while(!GH::g_window.shouldClose()) {
        GH::clearFrameIDs();
        PNT::processEvents();
        GH::g_window.startFrame();

        GH::drawGlobalDockingWindow();
        GH::drawMainMenuBar();
        GH::drawNodeTree();
        GH::drawNodeInspector();

        GH::g_window.endFrame();
    }

    for(GH::nodeRef scene : GH::g_scenes) {
        delete scene;
    }
    GH::g_scenes.clear();
    GH::g_currentScene = nullptr;

    PNT::deinit();
    return 0;
}
