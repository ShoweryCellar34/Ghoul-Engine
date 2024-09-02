#include "resourceManager.hpp"

#include <Pentagram.hpp>

resourceManager::~resourceManager() {
    for(std::pair<const std::filesystem::path&, const fileHandle&> data : resourceHandles) {
        const fileHandle& resourceHandle = data.second;
        const filePath& resourcePath = data.first;

        userLogger.get()->debug("Freeing file resource \"{}\" at path: {}", resourcePath, resourcePath);
        resourceHandle.get()->close();
        if(!resourceHandle.get()->good()) {
            userLogger.get()->warn("Error closing file resource, goodbit not set");
        }
    }
}

bool resourceManager::freeResource(const char* resourcePath) {
    if(resourceHandles.find(resourcePath) != resourceHandles.end()) {
        const fileHandle& resourceHandle = resourceHandles.at(resourcePath);

        userLogger.get()->debug("Freeing file resource \"{}\" at path: {}", resourcePath, resourcePath);
        resourceHandle.get()->close();
        if(!resourceHandle.get()->good()) {
            userLogger.get()->warn("Error closing file resource, goodbit not set");
            return false;
        }
    } else {
        userLogger.get()->warn("Unable to find file resource \"{}\" to close", resourcePath);
        return false;
    }
    return true;
}

fileHandle resourceManager::preloadResource(filePath resourcePath) {
    if(std::filesystem::status(resourcePath).type() != std::filesystem::file_type::none) {
        bool pathRefExists = false;
        for(std::pair<const std::filesystem::path&, const fileHandle&> data : resourceHandles) {
            const filePath& path = data.first;

            if(resourcePath == path) {
                pathRefExists = true;
            }
        }
        if(!pathRefExists) {
            if(!std::filesystem::exists(resourcePath)) {
                userLogger.get()->debug("Path \"{}\" does not exist, file will be created on write.", resourcePath);
            } else {
                userLogger.get()->debug("Opening path \"{}\".", resourcePath);
            }
            fileHandle newResource = fileHandle(&std::fstream(resourcePath));
            resourceHandles.insert({resourcePath, newResource});
            bool good = newResource.get()->good() ? true : false;
            if(!good) {
                userLogger.get()->warn("Good bit not set, stream may be corrupted, aborting operation.");
                return fileHandle(nullptr);
            }
            return newResource;
        } else {
            userLogger.get()->warn("File \"{}\" is already a registered resource, aborting operation.", resourcePath);
            return fileHandle(nullptr);
        }
    } else {
        userLogger.get()->warn("File \"{}\" is not a valid path, aborting operation.", resourcePath);
    }
}

fileHandle resourceManager::getResource(const char* resourcePath) {
    if(resourceHandles.find(resourcePath) != resourceHandles.end()) {
        return resourceHandles.at(resourcePath);
    } else {
        return preloadResource(resourcePath);
    }
}

filePath resourceManager::getResourcePath(const char* resourcePath) {
    if(resourceHandles.find(resourcePath) != resourceHandles.end()) {
        return resourcePath;
    } else {
        return "";
    }
}
