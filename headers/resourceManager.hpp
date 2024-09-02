#pragma once

#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <defines.hpp>

class resourceManager {
private:
    std::unordered_map<std::string, std::pair<fileHandle, std::filesystem::path>> resourceHandles;

public:
    resourceManager();
    ~resourceManager();

    bool freeResource(const char* nameRef);

    bool preloadResource(filePath path, const char* nameRef = "");

    fileHandle getResource(const char* nameRef);
    filePath getResourcePath(const char* nameRef);
};
