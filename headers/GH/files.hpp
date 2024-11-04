#pragma once

#include <GH/globalsAndDefines.hpp>

namespace GH {
    bool loadResource(const fs::path& path, const std::string& desiredAlias, bool isCore = false);
}
