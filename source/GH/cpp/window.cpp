#include <GH/cpp/window.hpp>

#include <PNT/init.hpp>
#include <GH/cpp/globalsAndDefines.hpp>

namespace GH::renderer {
    void init() {
        try {
            PNT::init();
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            GH::renderer::internal::g_window = new PNT::Window("WAITING FOR GAME", 300, 300, GLFW_DONT_CARE, GLFW_DONT_CARE, 0);
        } catch(const PNT::exception& error) {
            triggerError(GH::error::codes::CORE_RESOURCE_ERROR, error);
        }
        try {
            GH::renderer::internal::g_textureManager.setGL((GladGLContext*)GH::renderer::internal::g_window->getGL());
        } catch(const GH::error::exception& error) {
            GH::error::triggerError(GH::error::codes::CORE_RESOURCE_ERROR, error);
        }
    }

    void deinit() {
        PNT::deinit();
        delete GH::renderer::internal::g_window;
        GH::renderer::internal::g_window = nullptr;
    }

    void load() {
        PNT::windowData data;
        data.focused = true;
        data.width = GH::userSettings::g_width;
        data.height = GH::userSettings::g_height;
        data.title = GH::userSettings::g_name;

        try {
            GH::renderer::internal::g_window->setWindowData(data);
        } catch(const PNT::exception& error) {
            triggerError(GH::error::codes::CORE_RESOURCE_ERROR, error);
        }
    }
}
