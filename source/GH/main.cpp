#include <tinyfiledialogs.h>
#include <PNT/Pentagram.hpp>

#include <GH/globalsAndDefines.hpp>
#include <GH/error.hpp>
#include <GH/lua.hpp>

void eventCallback(PNT::Window* window, PNT::windowEvent event) {
    switch(event.type) {
    case PNT_EVENT_TYPE_KEYBOARD:
        switch(event.keyboard.key) {
        }
    }
}

int main(int argc, char* argv[]) {
#ifdef GAME_FOLDER
    *const_cast<char**>(&GH::g_gameFolder) = (char[])GAME_FOLDER;
#endif
#ifndef GAME_FOLDER
    if(argc > 1) {
        *const_cast<char**>(&GH::g_gameFolder) = argv[1];
    } else {
        *const_cast<char**>(&GH::g_gameFolder) = tinyfd_selectFolderDialog("Select game folder", nullptr);
    }
#endif
    if(GH::g_gameFolder == nullptr) {
        GH::error(GH::errors::GAME_FOLDER_NOT_SET);
    }
    if(!fs::exists(GH::g_gameFolder)) {
        GH::error(GH::errors::GAME_FOLDER_DOES_NOT_EXIST);
    }

    try {
        GH::g_resourceManager.loadResource("game resources", (fs::path)GH::g_gameFolder / "res.lua");
        userLogger.get()->info(GH::g_resourceManager.getData("game resources"));
    } catch(const std::exception& error) {
        userLogger.get()->error(error.what());
    }
    
    GH::lua();

    userLogger.get()->info("Finished successfully, exiting with code 0");
    return 0;
}
