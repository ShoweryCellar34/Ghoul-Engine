#include <tinyfiledialogs.h>
#include <Pentagram.hpp>

#include <globalsAndDefines.hpp>

void eventCallback(PNT::Window* window, PNT::windowEvent event) {
    switch(event.type) {
    case PNT_EVENT_TYPE_KEYBOARD:
        switch(event.keyboard.key) {
        }
    }
}

int main(int argc, char* argv[]) {
#ifdef GAME_FOLDER
    *const_cast<fs::path*>(&GH::g_gameFolder) = GAME_FOLDER;
#endif
#ifndef GAME_FOLDER
    if(argc > 1) {
        *const_cast<fs::path*>(&GH::g_gameFolder) = argv[1];
    } else {
        *const_cast<fs::path*>(&GH::g_gameFolder) = tinyfd_selectFolderDialog("Select game folder", nullptr);
    }
#endif
    if(GH::g_gameFolder == "") {
        GH::exit(GH::exitReason::NO_FOLDER_SET);
    }
    if(!fs::exists(GH::g_gameFolder)) {
        GH::exit(GH::exitReason::FOLDER_DOES_NOT_EXIST);
    }

    return 0;
}
