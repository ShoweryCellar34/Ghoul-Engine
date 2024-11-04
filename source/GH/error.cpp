#include <GH/error.hpp>

#include <PNT/Pentagram.hpp>

namespace GH {
    void triggerError(errors error, const std::string& data) {
        switch(error) {
        case errors::GAME_FOLDER_DOES_NOT_EXIST:
            ::userLogger.get()->error("Game folder \"{}\" does not exist, exiting with code {}", data, (int)error);
            exit((int)error);
            break;
        case errors::GAME_FOLDER_NOT_SET:
            ::userLogger.get()->error("Game folder not set, exiting with code {}", (int)error);
            exit((int)error);
            break;
        case errors::RESOURCE_ERROR:
            ::userLogger.get()->warn("Resource \"{}\" failed to load", data);
            break;
        case errors::CORE_RESOURCE_ERROR:
            ::userLogger.get()->error("Core resource \"{}\" failed to load, exiting with code {}", data, (int)error);
            exit((int)error);
            break;
        }
    }
}
