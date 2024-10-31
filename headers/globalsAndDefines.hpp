#pragma once

#include <filesystem>

#include <resourceManager.hpp>

namespace fs = std::filesystem;

namespace GH {
    inline resourceManager g_resourceManager;
    inline const fs::path g_gameFolder;
}
