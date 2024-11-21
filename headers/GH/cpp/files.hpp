#pragma once

#include <GH/cpp/resourceManager.hpp>

namespace GH::resources {
    bool wasSuccessful();

    void loadResource(const std::string& desiredAlias, const fs::path& path, bool isCore, perms permitions);
    void unloadResource(const std::string& alias);
    void unloadAllResources();
    std::string getData(const std::string& alias);
}
