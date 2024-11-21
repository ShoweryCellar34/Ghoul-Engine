#include <GH/lua/luaMain.hpp>

#include <tinyfiledialogs.h>

#include <GH/cpp/globalsAndDefines.hpp>
#include <GH/cpp/error.hpp>
#include <GH/cpp/files.hpp>
#include <GH/cpp/resourceManager.hpp>
#include <GH/lua/scripting.hpp>

int luaMain(int argc, char* argv[]) {
#ifdef GH_GAME_FOLDER
    *const_cast<char**>(&GH::g_gameFolder) = (char[])GH_GAME_FOLDER;
#endif
#ifndef GH_GAME_FOLDER
    if(argc > 1) {
        *const_cast<char**>(&GH::g_gameFolder) = argv[1];
    } else {
        *const_cast<char**>(&GH::g_gameFolder) = tinyfd_selectFolderDialog("Select game folder", argv[0]);
    }
#endif
    userLogger.get()->set_level(spdlog::level::trace);

    if(GH::g_gameFolder == nullptr) {
        GH::error::triggerError(GH::error::codes::GAME_FOLDER_NOT_SET);
    }
    if(!fs::exists(GH::g_gameFolder)) {
        GH::error::triggerError(GH::error::codes::GAME_FOLDER_DOES_NOT_EXIST);
    }


    GH::resources::loadResource("GAME_SETTINGS", "settings.lua", true, GH::resources::perms(true, false));
    GH::lua::run(GH::resources::getData("GAME_SETTINGS"));

    PNT::init();

    std::string name = GH::lua::getString("GAME_NAME", true);
    std::string icon = GH::lua::getString("GAME_ICON", false);
    int widthResult = GH::lua::getNumber("GAME_WIDTH", false);
    uint32_t width = GH::lua::wasSuccessful() ? widthResult : 1600;
    int heightResult = GH::lua::getNumber("GAME_HEIGHT", false);
    uint32_t height = GH::lua::wasSuccessful() ? heightResult : 900;

    GH::resources::loadResource("GAME_ICON", icon, false, GH::resources::perms(true, false));

    try {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        GH::renderer::internal::g_window = new PNT::Window(name, width, height, GLFW_DONT_CARE, GLFW_DONT_CARE, 0);
        // GH::renderer::internal::g_window->setIcon();
    } catch(const PNT::exception& error) {
        GH::error::triggerError(GH::error::codes::CORE_PNT_ERROR, error);
    }

    while(!GH::renderer::internal::g_window->shouldClose()) {
        PNT::processEvents();
        GH::renderer::internal::g_window->startFrame();

        GH::renderer::internal::g_window->endFrame();
    }

    PNT::deinit();
    GH::resources::unloadAllResources();
    userLogger.get()->info("Finished successfully, exiting with code 0");
    return 0;
}
