#pragma once

#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <defines.hpp>

class resourceManager {
private:
    std::unordered_map<std::filesystem::path, fileHandle> resourceHandles;

public:
    resourceManager();
    ~resourceManager();

    bool freeResource(const char* nameRef);

    fileHandle preloadResource(filePath resourcePath);

    fileHandle getResource(const char* nameRef);
    filePath getResourcePath(const char* nameRef);
};
