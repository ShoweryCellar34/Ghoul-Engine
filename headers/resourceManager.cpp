#include "resourceManager.hpp"

#include <Pentagram.hpp>

resourceManager::~resourceManager() {
    for(std::pair<char*, std::pair<const fileHandle, std::filesystem::path>> data : handles) {
        const std::pair<const fileHandle, std::filesystem::path>& handleData = data.second;
        const fileHandle& handle = handleData.first;
        const std::filesystem::path& path = handleData.second;

        userLogger.get()->info("Freeing file resource \"{}\" at path: {}", data.first, path);
        handle.get()->close();
        if(!handle.get()->good()) {
            userLogger.get()->warn("Error closing file resource goodbit not set");
        }
    }
}

bool resourceManager::closeFile(const char* nameRef) {
    if(handles.find((char*)nameRef) != handles.end()) {
        const std::pair<const fileHandle, std::filesystem::path>& handleData = handles.at((char*)nameRef);
        const fileHandle& handle = handleData.first;
        const std::filesystem::path& path = handleData.second;

        userLogger.get()->info("Freeing file resource \"{}\" at path: {}", nameRef, path);
        handle.get()->close();
        if(!handle.get()->good()) {
            userLogger.get()->warn("Error closing file resource, goodbit not set");
            return false;
        }
    } else {
        userLogger.get()->warn("Unable to find file resource \"{}\" to close", nameRef);
        return false;
    }
    return true;
}
