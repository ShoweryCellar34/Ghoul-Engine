#include "resourceManager.hpp"

#include <Pentagram.hpp>

void resourceManager::internalClose(fileHandle handle) {
    userLogger.get()->info("Freeing file resource at path: {}", handle.);
    handle.get()->close();
}

resourceManager::~resourceManager()
{
    for(std::tuple<const fileHandle, std::filesystem::path, char*> handle : handles) {
        userLogger.get()->info("Freeing file resource \"{}\" at path: {}", handle., file);
        handle.first.get()->close();
    }
}

bool resourceManager::closeFile(const char *path) {
}
