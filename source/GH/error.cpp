#include <GH/error.hpp>

#include <PNT/Pentagram.hpp>

namespace GH {
    void error(errors error) {
        switch(error) {
        case errors::GAME_FOLDER_DOES_NOT_EXIST:
            ::userLogger.get()->error("Game folder does not exist, exiting with code {}", (int)error);
            exit((int)error);
            break;
        case errors::GAME_FOLDER_NOT_SET:
            ::userLogger.get()->error("Game folder not set, exiting with code {}", (int)error);
            exit((int)error);
            break;
        }
    }
}
