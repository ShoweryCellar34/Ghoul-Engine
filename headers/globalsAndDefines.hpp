#pragma once

#include <filesystem>

#include <resourceManager.hpp>

namespace fs = std::filesystem;

namespace GH {
    inline resourceManager g_resourceManager;
    inline const fs::path g_gameFolder;

    enum class exitReason {
        NO_FOLDER_SET = 1,
        FOLDER_DOES_NOT_EXIST
    };
}
