#pragma once

#include <string>
#include <GH/cpp/globalsAndDefines.hpp>

namespace GH::renderer {
    bool wasSuccessful();

    void loadTexture(const std::string& desiredAlias, const std::string& data, bool isCore);
    void loadTexture(const std::string& desiredAlias, const fs::path& path, bool isCore);
    void unloadTexture(const std::string& alias);
    void unloadAllTextures();

    int getWidth(const std::string& alias, bool isCore);
    int getHeight(const std::string& alias, bool isCore);
}
