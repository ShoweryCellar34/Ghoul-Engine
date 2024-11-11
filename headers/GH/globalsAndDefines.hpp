#pragma once

#include <filesystem>

#include <GH/resourceManager.hpp>
#include <GH/lua/luaManager.hpp>

namespace fs = std::filesystem;

namespace GH {
    namespace resources::internal {
        inline resourceManager g_resourceManager;
    }
    namespace lua::internal {
        inline luaState g_luaState;
    }
    inline const char* g_gameFolder;
}
