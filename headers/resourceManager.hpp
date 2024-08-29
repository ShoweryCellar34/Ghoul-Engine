#pragma once

#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <defines.hpp>

class resourceManager {
private:
    std::unordered_map<fileHandle, std::filesystem::path, char*> handles;

    void internalClose(fileHandle handle);

public:
    resourceManager();
    ~resourceManager();

    bool closeFile(const char* path);
    bool closeFile(fileHandle path);

    bool openFile(const char* path);

    fileHandle getFile(const char* path);
};
