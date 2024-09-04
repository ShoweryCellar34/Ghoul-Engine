#include "resourceManager.hpp"

#include <Pentagram.hpp>

void resourceManager::bitCheck(std::ios_base::iostate bit) {
    if(bit != std::ios_base::goodbit) {
        switch(bit) {
        case std::ios_base::badbit:
            throw "Bad bit is set, stream may be corrupted, aborting operation.";
            break;
        case std::ios_base::failbit:
            throw "Fail bit is set, operation may have failed, aborting operation.";
            break;
        default:
            throw "Good bit not set, unknown error, aborting operation";
            break;
        }
    }
}

resourceManager::~resourceManager()
{
    for(std::pair<const std::filesystem::path&, const fileHandle&> data : resourceHandles) {
        const fileHandle& resourceHandle = data.second;
        const filePath& resourcePath = data.first;

        userLogger.get()->debug("Freeing file resource at path \"{}\"", resourcePath.string());
        resourceHandle.get()->flush();
        resourceHandle.get()->close();
        bitCheck(resourceHandle.get()->rdstate());
    }
}

void resourceManager::freeResource(filePath resourcePath) {
    if(resourceHandles.find(resourcePath) != resourceHandles.end()) {
        const fileHandle& resourceHandle = resourceHandles.at(resourcePath);

        userLogger.get()->debug("Freeing file resource at path \"{}\"", resourcePath.string());
        resourceHandle.get()->flush();
        resourceHandle.get()->close();
        bitCheck(resourceHandle.get()->rdstate());
    } else {
        throw "Unable to find file resource \"" + resourcePath.string() + "\" to close.";
    }
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
                userLogger.get()->debug("Path \"{}\" does not exist, file will be created on write.", resourcePath.string());
            } else {
                userLogger.get()->debug("Opening path \"{}\".", resourcePath.string());
            }
            fileHandle newResource = std::make_shared<std::fstream>(resourcePath);
            resourceHandles.insert({resourcePath, newResource});
            bitCheck(newResource.get()->rdstate());
            return newResource;
        } else {
            throw "File \"" + resourcePath.string() + "\" is already a registered resource, aborting operation.";
            return fileHandle(nullptr);
        }
    } else {
        throw "File \"" + resourcePath.string() + "\" is not a valid path, aborting operation.";
        return fileHandle(nullptr);
    }
}

fileHandle resourceManager::getResource(const char* resourcePath) {
    if(resourceHandles.find(resourcePath) != resourceHandles.end()) {
        return resourceHandles.at(resourcePath);
    } else {
        return preloadResource(resourcePath);
    }
}
