#include <GH/cpp/images.hpp>

#include <unordered_map>

namespace GH::renderer {
    bool success = false;
    std::unordered_map<std::string, bool> resources;

    bool wasSuccessful() {
        return success;
    }

    void loadTexture(const std::string& desiredAlias, const std::string& data, bool isCore) {
        if(resources.find(desiredAlias) != resources.end()) {
            if(resources.at(desiredAlias)) {
                if(isCore) {
                    error::triggerError(error::codes::CORE_RESOURCE_ERROR, error::exception("Core texture \"" + desiredAlias + "\" already registered with the \"GH::resources::loadResource()\" function (if you unregistered the texture alias in any way other than the \"GH::resources::unloadResource()\" function)"));
                } else {
                    error::triggerError(error::codes::RESOURCE_ERROR, error::exception("Core texture \"" + desiredAlias + "\" already registered with the \"GH::resources::loadResource()\" function (if you unregistered the texture alias in any way other than the \"GH::resources::unloadResource()\" function)"));
                }
            } else {
                if(isCore) {
                    error::triggerError(error::codes::CORE_RESOURCE_ERROR, error::exception("Non-core texture \"" + desiredAlias + "\" already registered with the \"GH::resources::loadResource()\" function (if you unregistered the texture alias in any way other than the \"GH::resources::unloadResource()\" function)"));
                } else {
                    error::triggerError(error::codes::RESOURCE_ERROR, error::exception("Non-core texture \"" + desiredAlias + "\" already registered with the \"GH::resources::loadResource()\" function (if you unregistered the texture alias in any way other than the \"GH::resources::unloadResource()\" function)"));
                }
            }
            success = false;
            return;
        }
        try {
            internal::g_textureManager.loadTexture(desiredAlias, data);
            resources.insert({desiredAlias, isCore});
            if(isCore) {
                ::userLogger.get()->info("Loaded core texture at path \"{}\" with texture alias \"{}\" successfully", path.string(), desiredAlias);
            } else {
                ::userLogger.get()->info("Loaded non-core texture at path \"{}\" with texture alias \"{}\" successfully", path.string(), desiredAlias);
            }
            success = true;
        } catch(const error::exception& error) {
            if(isCore) {
                triggerError(GH::error::codes::CORE_RESOURCE_ERROR, error);
            } else {
                triggerError(GH::error::codes::RESOURCE_ERROR, error);
            }
            success = false;
        }
    }

    void loadTexture(const std::string& desiredAlias, const fs::path& path, bool isCore) {
    }

    void unloadTexture(const std::string& alias) {
        if(resources.find(alias) == resources.end()) {
            error::triggerError(error::codes::RESOURCE_ERROR, error::exception("Alias \"" + alias + "\" not registered (if you registered the texture alias in any way other than the \"GH::resources::loadResource()\" function, that may be the cause of this error)"));
            success = false;
            return;
        }
        try {
            internal::g_textureManager.unloadTexture(alias);
            resources.erase(alias);
            if(resources.at(alias)) {
                ::userLogger.get()->trace("Unloaded core texture with texture alias \"{}\" successfully", alias);
            } else {
                ::userLogger.get()->trace("Unloaded non-core texture with texture alias \"{}\" successfully", alias);
            }
            success = true;
        } catch(const error::exception& error) {
            if(resources.at(alias)) {
                triggerError(GH::error::codes::CORE_RESOURCE_ERROR, error);
            } else {
                triggerError(GH::error::codes::RESOURCE_ERROR, error);
            }
            success = false;
        }
    }

    void unloadAllTextures() {
        for(const std::pair<std::string, bool>& texture : resources) {
            try {
                internal::g_textureManager.unloadTexture(texture.first);
                if(texture.second) {
                    ::userLogger.get()->trace("Unloaded core texture with texture alias \"{}\" successfully", texture.first);
                } else {
                    ::userLogger.get()->trace("Unloaded non-core texture with texture alias \"{}\" successfully", texture.first);
                }
            } catch(const error::exception& error) {
                if(texture.second) {
                    triggerError(GH::error::codes::CORE_RESOURCE_ERROR, error);
                } else {
                    triggerError(GH::error::codes::RESOURCE_ERROR, error);
                }
                success = false;
                return;
            }
        }
        resources.clear();
        success = true;
    }


    int getWidth(const std::string& alias) {
    }

    int getHeight(const std::string& alias) {
    }
}
