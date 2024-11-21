#include <GH/cpp/files.hpp>

#include <unordered_map>
#include <PNT/Pentagram.hpp>
#include <GH/cpp/globalsAndDefines.hpp>
#include <GH/cpp/error.hpp>

namespace GH::resources {
    bool success = false;
    std::unordered_map<std::string, bool> resources;

    bool wasSuccessful() {
        return success;
    }

    void loadResource(const std::string& desiredAlias, const fs::path& path, bool isCore, perms permitions) {
        if(resources.find(desiredAlias) != resources.end()) {
            if(resources.at(desiredAlias)) {
                if(isCore) {
                    error::triggerError(error::codes::CORE_FILE_ERROR, error::exception("Core resource \"" + desiredAlias + "\" already registered with the \"GH::resources::loadResource()\" function (if you unregistered the resource alias in any way other than the \"GH::resources::unloadResource()\" function)"));
                } else {
                    error::triggerError(error::codes::FILE_ERROR, error::exception("Core resource \"" + desiredAlias + "\" already registered with the \"GH::resources::loadResource()\" function (if you unregistered the resource alias in any way other than the \"GH::resources::unloadResource()\" function)"));
                }
            } else {
                if(isCore) {
                    error::triggerError(error::codes::CORE_FILE_ERROR, error::exception("Non-core resource \"" + desiredAlias + "\" already registered with the \"GH::resources::loadResource()\" function (if you unregistered the resource alias in any way other than the \"GH::resources::unloadResource()\" function)"));
                } else {
                    error::triggerError(error::codes::FILE_ERROR, error::exception("Non-core resource \"" + desiredAlias + "\" already registered with the \"GH::resources::loadResource()\" function (if you unregistered the resource alias in any way other than the \"GH::resources::unloadResource()\" function)"));
                }
            }
            success = false;
            return;
        }
        try {
            internal::g_resourceManager.loadResource(desiredAlias, (fs::path)GH::g_gameFolder / path, permitions, true);
            resources.insert({desiredAlias, isCore});
            if(isCore) {
                ::userLogger.get()->info("Loaded core resource at path \"{}\" with resource alias \"{}\" successfully", path.string(), desiredAlias);
            } else {
                ::userLogger.get()->info("Loaded non-core resource at path \"{}\" with resource alias \"{}\" successfully", path.string(), desiredAlias);
            }
            success = true;
        } catch(const error::exception& error) {
            if(isCore) {
                triggerError(GH::error::codes::CORE_FILE_ERROR, error);
            } else {
                triggerError(GH::error::codes::FILE_ERROR, error);
            }
            success = false;
        }
    }

    void unloadResource(const std::string& alias) {
        if(resources.find(alias) == resources.end()) {
            error::triggerError(error::codes::FILE_ERROR, error::exception("Resource alias \"" + alias + "\" not registered (if you registered the resource alias in any way other than the \"GH::resources::loadResource()\" function, that may be the cause of this error)"));
            success = false;
            return;
        }
        try {
            internal::g_resourceManager.unloadResource(alias);
            resources.erase(alias);
            if(resources.at(alias)) {
                ::userLogger.get()->trace("Unloaded core resource with resource alias \"{}\" successfully", alias);
            } else {
                ::userLogger.get()->trace("Unloaded non-core resource with resource alias \"{}\" successfully", alias);
            }
            success = true;
        } catch(const error::exception& error) {
            if(resources.at(alias)) {
                triggerError(GH::error::codes::CORE_FILE_ERROR, error);
            } else {
                triggerError(GH::error::codes::FILE_ERROR, error);
            }
            success = false;
        }
    }

    void unloadAllResources() {
        for(const std::pair<std::string, bool>& resource : resources) {
            try {
                internal::g_resourceManager.unloadResource(resource.first);
                if(resource.second) {
                    ::userLogger.get()->trace("Unloaded core resource with resource alias \"{}\" successfully", resource.first);
                } else {
                    ::userLogger.get()->trace("Unloaded non-core resource with resource alias \"{}\" successfully", resource.first);
                }
            } catch(const error::exception& error) {
                if(resource.second) {
                    triggerError(GH::error::codes::CORE_FILE_ERROR, error);
                } else {
                    triggerError(GH::error::codes::FILE_ERROR, error);
                }
                success = false;
                return;
            }
        }
        resources.clear();
        success = true;
    }

    std::string getData(const std::string& alias) {
        if(resources.find(alias) == resources.end()) {
            error::triggerError(error::codes::FILE_ERROR, error::exception("Resource alias \"" + alias + "\" not registered (if you registered the resource alias in any way other than the \"GH::resources::loadResource()\" function, that may be the cause of this error)"));
            return "";
        }
        try {
            std::string data = internal::g_resourceManager.getData(alias);
            if(resources.at(alias)) {
                ::userLogger.get()->trace("Read data from core resource with resource alias \"{}\" successfully", alias);
            } else {
                ::userLogger.get()->trace("Read data from non-core resource with resource alias \"{}\" successfully", alias);
            }
            return data;
        } catch(const error::exception& error) {
            if(resources.at(alias)) {
                triggerError(GH::error::codes::CORE_FILE_ERROR, error);
            } else {
                triggerError(GH::error::codes::FILE_ERROR, error);
            }
            return "";
        }
    }
}
