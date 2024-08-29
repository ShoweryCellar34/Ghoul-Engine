#pragma once

#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <defines.hpp>

class resourceManager {
private:
    std::unordered_map<char*, std::pair<fileHandle, std::filesystem::path>> handles;

public:
    resourceManager();
    ~resourceManager();

    bool closeFile(const char* nameRef);

    bool openFile(const char* nameRef);

    fileHandle getFile(const char* nameRef);
};
