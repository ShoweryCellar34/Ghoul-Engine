#include <tinyfiledialogs.h>
#include <PNT/Pentagram.hpp>

#include <GH/globalsAndDefines.hpp>
#include <GH/error.hpp>
#include <GH/files.hpp>
#include <GH/resourceManager.hpp>
#include <GH/lua.hpp>

void eventCallback(PNT::Window* window, PNT::windowEvent event) {
    switch(event.type) {
    case PNT_EVENT_TYPE_KEYBOARD:
        switch(event.keyboard.key) {
        }
    }
}

int main(int argc, char* argv[]) {
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
        GH::triggerError(GH::errors::GAME_FOLDER_NOT_SET);
    }
    if(!fs::exists(GH::g_gameFolder)) {
        GH::triggerError(GH::errors::GAME_FOLDER_DOES_NOT_EXIST);
    }

    GH::resources::loadResource("GAME_MAIN", "main.lua", true, GH::resources::perms(true, false));
    userLogger.get()->info(GH::resources::getData("GAME_MAIN"));
    GH::resources::unloadResource("GAME_MAIN");

    userLogger.get()->info("Finished successfully, exiting with code 0");
    return 0;
}
