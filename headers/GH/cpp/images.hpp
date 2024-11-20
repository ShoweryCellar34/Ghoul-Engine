#pragma once

#include <string>

namespace GH::renderer {
    bool loadTexture(const std::string& desiredAlias, const std::string& data, bool isCore);
    bool unloadTexture(const std::string& alias);
    bool unloadAllTextures();

    std::pair<int, bool> getWidth(const std::string& alias, bool isCore);
    std::pair<int, bool> getHeight(const std::string& alias, bool isCore);
}
