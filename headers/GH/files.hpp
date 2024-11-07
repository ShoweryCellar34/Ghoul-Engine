#pragma once

#include <GH/globalsAndDefines.hpp>

namespace GH::resources {
    bool loadResource(const std::string& desiredAlias, const fs::path& path, bool isCore = false, std::ios_base::openmode permitions = std::ios::in);
    bool unloadResource(const std::string& alias);
    std::string getData(const std::string& alias);
}
