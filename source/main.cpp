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
#ifdef GAME_FOLDER
    char* gameFolder = GAME_FOLDER;
#endif
#ifndef GAME_FOLDER
    char* gameFolder;
    if(argc > 1) {
        gameFolder = argv[1];
    } else {
        gameFolder = tinyfd_selectFolderDialog("Select game folder", nullptr);
    }
#endif

    if(gameFolder == nullptr) {
        exit(EXIT_FAILURE);
    }

    userLogger.get()->info(gameFolder);

    return 0;
}
