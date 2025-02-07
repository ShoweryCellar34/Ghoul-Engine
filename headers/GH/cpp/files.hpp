#pragma once

#include <RM/RM.hpp>

namespace GH::resources {
    bool wasSuccessful();

    void loadResource(const std::string& desiredAlias, const fs::path& path, bool isCore, RM::mode permitions);
    void unloadResource(const std::string& alias);
    void unloadAllResources();
    std::string getData(const std::string& alias);
}
