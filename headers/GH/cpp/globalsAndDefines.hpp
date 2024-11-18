#pragma once

#include <filesystem>
#include <PNT/Pentagram.hpp>
#include <GH/cpp/resourceManager.hpp>
#include <GH/lua/luaManager.hpp>

namespace fs = std::filesystem;

namespace GH {
    namespace resources::internal {
        inline resourceManager g_resourceManager;
    }
    namespace lua::internal {
        inline luaState g_luaState;
    }
    namespace renderer::internal {
        inline PNT::Window* g_window = nullptr;
    }
    inline const char* g_gameFolder;
}
