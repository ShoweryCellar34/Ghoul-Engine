#include "resourceManager.hpp"

#include <Pentagram.hpp>

resourceManager::~resourceManager() {
    for(std::pair<const std::string&, std::pair<const fileHandle, filePath>> data : resourceHandles) {
        const std::pair<const fileHandle, filePath>& handleData = data.second;
        const fileHandle& handle = handleData.first;
        const filePath& path = handleData.second;

        userLogger.get()->debug("Freeing file resource \"{}\" at path: {}", data.first, path);
        handle.get()->close();
        if(!handle.get()->good()) {
            userLogger.get()->warn("Error closing file resource goodbit not set");
        }
    }
}

bool resourceManager::freeResource(const char* nameRef) {
    if(resourceHandles.find(nameRef) != resourceHandles.end()) {
        const std::pair<const fileHandle, filePath>& handleData = resourceHandles.at(nameRef);
        const fileHandle& handle = handleData.first;
        const filePath& path = handleData.second;

        userLogger.get()->debug("Freeing file resource \"{}\" at path: {}", nameRef, path);
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

bool resourceManager::preloadResource(filePath resourcePath, const char* nameRef) {
    bool nameExists = false;
    for(std::pair<const std::string&, std::pair<const fileHandle, filePath>> data : resourceHandles) {
        const fileHandle& name = handleData.first;

        if(nameRef == name) {
            nameExists = true;
        }
    }
    if(!nameExists) {
        if(!std::filesystem::exists(resourcePath)) {
            userLogger.get()->debug("Path \"{}\" does not exist, file will be created on write.", resourcePath);
        } else {
            userLogger.get()->debug("Opening path \"{}\".", resourcePath);
        }
        fileHandle newHandle = fileHandle(std::fstream(resourcePath));
        resourceHandles.insert(nameRef, std::make_pair<fileHandle, resourcePath>(newHandle, resourcePath));
        bool good = newHandle.get()->good() ? true : false;
        if(!good) {
            userLogger.get()->warn("Good bit not set, stream may be corrupted, aborting operation.");
            return fileHandle(nullptr);
        }
        return newHandle;
    } else {
        userLogger.get()->warn("File name reference \"{}\" already exists, aborting operation.", nameRef);
        return fileHandle(nullptr);
    }
}

fileHandle resourceManager::getResource(const char* nameRef) {
    if(resourceHandles.find(nameRef) != resourceHandles.end()) {
        return resourceHandles.at(nameRef).first;
    } else {
        // path arg check
        return fileHandle(nullptr);
    }
}

filePath resourceManager::getResourcePath(const char* nameRef) {
    if(resourceHandles.find(nameRef) != resourceHandles.end()) {
        return resourceHandles.at(nameRef).second;
    } else {
        return "";
    }
}
