#pragma once

#include <filesystem>
#include <PNT/Pentagram.hpp>
#include <GH/cpp/resourceManager.hpp>
#include <GH/lua/luaManager.hpp>
#include <GH/cpp/textureManager.hpp>

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
        inline textureManager g_textureManager;
    }
    namespace userSettings {
        inline std::string g_name;
        inline std::string g_mainScenePath;
        inline std::string g_iconPath;
        inline int g_width = 0;
        inline int g_height = 0;
    }
    inline const char* g_gameFolder;
}
