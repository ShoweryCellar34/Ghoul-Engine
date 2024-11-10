#pragma once

#include <GH/resourceManager.hpp>

namespace GH::resources {
    bool loadResource(const std::string& desiredAlias, const fs::path& path, bool isCore = false, perms permitions = perms(true, false));
    bool unloadResource(const std::string& alias);
    bool unloadAllResources();
    std::string getData(const std::string& alias);
}
