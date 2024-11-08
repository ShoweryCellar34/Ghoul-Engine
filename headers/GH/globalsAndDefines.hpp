#pragma once

#include <filesystem>

#include <GH/resourceManager.hpp>
#include <GH/lua.hpp>

namespace fs = std::filesystem;

namespace GH {
    namespace resources::internal {
        inline resourceManager g_resourceManager;
    }
    namespace lua::internal {
        inline luaState g_luaState;
    }
    inline const char* g_gameFolder;

    enum class errors {
        GAME_FOLDER_NOT_SET,
        GAME_FOLDER_DOES_NOT_EXIST,
        CORE_RESOURCE_ERROR,
        RESOURCE_ERROR,
        CORE_LUA_ERROR,
        LUA_ERROR
    };
}
