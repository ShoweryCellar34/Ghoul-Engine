#include <GH/files.hpp>

#include <unordered_map>
#include <PNT/Pentagram.hpp>
#include <GH/globalsAndDefines.hpp>
#include <GH/error.hpp>

namespace GH::resources {
    std::unordered_map<std::string, bool> resources;

    bool loadResource(const std::string& desiredAlias, const fs::path& path, bool isCore, perms permitions) {
        try {
            internal::g_resourceManager.loadResource(desiredAlias, (fs::path)GH::g_gameFolder / path, permitions, true);
            resources.insert({desiredAlias, isCore});
            if(isCore) {
                ::userLogger.get()->info("Loaded core resource at path \"{}\" with alias \"{}\" successfully", path.string(), desiredAlias);
            } else {
                ::userLogger.get()->info("Loaded resource at path \"{}\" with alias \"{}\" successfully", path.string(), desiredAlias);
            }
            return true;
        } catch(const std::exception& error) {
            if(isCore) {
                triggerError(GH::errors::CORE_RESOURCE_ERROR, error.what());
            } else {
                triggerError(GH::errors::RESOURCE_ERROR, error.what());
            }
            return false;
        }
    }

    bool unloadResource(const std::string& alias) {
        try {
            internal::g_resourceManager.unloadResource(alias);
            resources.erase(alias);
            ::userLogger.get()->info("Unloaded resource with alias \"{}\" successfully", alias);
            return true;
        } catch(const std::exception& error) {
            if(resources.at(alias)) {
                triggerError(GH::errors::CORE_RESOURCE_ERROR, error.what());
            } else {
                triggerError(GH::errors::RESOURCE_ERROR, error.what());
            }
            return false;
        }
    }

    std::string getData(const std::string& alias) {
        try {
            std::string data = internal::g_resourceManager.getData(alias);
            ::userLogger.get()->trace("Read data from resource with alias \"{}\" successfully", alias);
            return data;
        } catch(const std::exception& error) {
            if(resources.at(alias)) {
                triggerError(GH::errors::CORE_RESOURCE_ERROR, error.what());
            } else {
                triggerError(GH::errors::RESOURCE_ERROR, error.what());
            }
            return "";
        }
    }
}
