#pragma once

#include <GH/cpp/resourceManager.hpp>

namespace GH::resources {
    bool loadResource(const std::string& desiredAlias, const fs::path& path, bool isCore, perms permitions);
    bool unloadResource(const std::string& alias);
    bool unloadAllResources();
    std::string getData(const std::string& alias);
}
