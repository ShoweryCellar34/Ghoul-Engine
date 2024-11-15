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

    GH::resources::loadResource("GAME_MAIN", "main.lua", true, GH::resources::perms(true, false));

    GH::resources::unloadAllResources();
    userLogger.get()->info("Finished successfully, exiting with code 0");
    return 0;
}
