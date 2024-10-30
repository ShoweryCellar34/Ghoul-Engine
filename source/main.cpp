#include <tinyfiledialogs.h>
#include <Pentagram.hpp>

#include <resourceManager.hpp>
#include <texture.hpp>

void eventCallback(PNT::Window* window, PNT::windowEvent event) {
    switch(event.type) {
    case PNT_EVENT_TYPE_KEYBOARD:
        switch(event.keyboard.key) {
        }
    }
}

int main(int argc, char* argv[]) {
    const fs::path gameFolder;
#ifdef GAME_FOLDER
    *const_cast<fs::path*>(&gameFolder) = GAME_FOLDER;
#endif
#ifndef GAME_FOLDER
    if(argc > 1) {
        *const_cast<fs::path*>(&gameFolder) = argv[1];
    } else {
        *const_cast<fs::path*>(&gameFolder) = tinyfd_selectFolderDialog("Select game folder", nullptr);
    }
#endif

    if(gameFolder == "") {
        exit(EXIT_FAILURE);
    }
    if(!fs::exists(gameFolder)) {
        exit(EXIT_FAILURE);
    }

    userLogger.get()->info(gameFolder.string());

    return 0;
}
