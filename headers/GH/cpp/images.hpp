#pragma once

#include <string>
#include <GH/cpp/globalsAndDefines.hpp>

namespace GH::renderer {
    bool wasSuccessful();

    void loadTexture(const std::string& desiredAlias, const std::string& data, bool isCore);
    void unloadTexture(const std::string& alias);
    void unloadAllTextures();

    std::string getTextureData(const std::string& alias);
    unsigned char* const getRawTextureData(const std::string& alias);
    int getTextureWidth(const std::string& alias);
    int getTextureHeight(const std::string& alias);
}
