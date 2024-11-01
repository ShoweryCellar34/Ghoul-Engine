#pragma once

#include <filesystem>

#include <GH/resourceManager.hpp>

namespace fs = std::filesystem;

namespace GH {
    inline resourceManager g_resourceManager;
    inline const char* g_gameFolder;

    enum class errors {
        GAME_FOLDER_NOT_SET,
        GAME_FOLDER_DOES_NOT_EXIST
    };
}
