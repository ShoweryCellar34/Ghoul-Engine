#include <GH/lua/luaMain.hpp>

#include <tinyfiledialogs.h>

#include <GH/cpp/globalsAndDefines.hpp>
#include <GH/cpp/error.hpp>
#include <GH/cpp/files.hpp>
#include <GH/cpp/resourceManager.hpp>
#include <GH/cpp/window.hpp>
#include <GH/lua/scripting.hpp>
#include <GH/cpp/images.hpp>

void setGameFolder(int argc, char* argv[]) {
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

    if(GH::g_gameFolder == nullptr) {
        GH::error::triggerError(GH::error::codes::GAME_FOLDER_NOT_SET);
    }
    if(!fs::exists(GH::g_gameFolder)) {
        GH::error::triggerError(GH::error::codes::GAME_FOLDER_DOES_NOT_EXIST);
    }
}

void initialize(int argc, char* argv[]) {
    userLogger.get()->set_level(spdlog::level::trace);
    setGameFolder(argc, argv);
    GH::renderer::init();
    GH::lua::loadSettings();
    GH::renderer::load();
}

void deinit() {
    GH::renderer::deinit();
    GH::resources::unloadAllResources();
    GH::renderer::unloadAllTextures();
    userLogger.get()->info("Finished successfully, exiting with code 0");
}

int luaMain(int argc, char* argv[]) {
    initialize(argc, argv);

    while(!GH::renderer::internal::g_window->shouldClose()) {
        PNT::processEvents();
        GH::renderer::internal::g_window->startFrame();

        GH::renderer::internal::g_window->endFrame();
    }

    deinit();
    return (int)GH::error::codes::SUCCESS;
}
