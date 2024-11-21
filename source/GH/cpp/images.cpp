#include <GH/cpp/images.hpp>

#include <unordered_map>

namespace GH::renderer {
    bool success = false;
    std::unordered_map<std::string, bool> textures;

    bool wasSuccessful() {
        return success;
    }

    void loadTexture(const std::string& desiredAlias, const std::string& data, bool isCore) {
        if(textures.find(desiredAlias) != textures.end()) {
            if(textures.at(desiredAlias)) {
                if(isCore) {
                    error::triggerError(error::codes::CORE_RESOURCE_ERROR, error::exception("Core texture \"" + desiredAlias + "\" already registered with the \"GH::renderer::loadTexture()\" function (if you unregistered the texture alias in any way other than the \"GH::renderer::unloadTexture()\" function)"));
                } else {
                    error::triggerError(error::codes::RESOURCE_ERROR, error::exception("Core texture \"" + desiredAlias + "\" already registered with the \"GH::renderer::loadTexture()\" function (if you unregistered the texture alias in any way other than the \"GH::renderer::unloadTexture()\" function)"));
                }
            } else {
                if(isCore) {
                    error::triggerError(error::codes::CORE_RESOURCE_ERROR, error::exception("Non-core texture \"" + desiredAlias + "\" already registered with the \"GH::renderer::loadTexture()\" function (if you unregistered the texture alias in any way other than the \"GH::renderer::unloadTexture()\" function)"));
                } else {
                    error::triggerError(error::codes::RESOURCE_ERROR, error::exception("Non-core texture \"" + desiredAlias + "\" already registered with the \"GH::renderer::loadTexture()\" function (if you unregistered the texture alias in any way other than the \"GH::renderer::unloadTexture()\" function)"));
                }
            }
            success = false;
            return;
        }
        try {
            internal::g_textureManager.loadTexture(desiredAlias, data);
            textures.insert({desiredAlias, isCore});
            if(isCore) {
                ::userLogger.get()->info("Loaded core texture with texture alias \"{}\" successfully", desiredAlias);
            } else {
                ::userLogger.get()->info("Loaded non-core texture with texture alias \"{}\" successfully", desiredAlias);
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
        if(textures.find(alias) == textures.end()) {
            error::triggerError(error::codes::RESOURCE_ERROR, error::exception("Alias \"" + alias + "\" not registered (if you registered the texture alias in any way other than the \"GH::renderer::loadTexture()\" function, that may be the cause of this error)"));
            success = false;
            return;
        }
        try {
            internal::g_textureManager.unloadTexture(alias);
            textures.erase(alias);
            if(textures.at(alias)) {
                ::userLogger.get()->trace("Unloaded core texture with texture alias \"{}\" successfully", alias);
            } else {
                ::userLogger.get()->trace("Unloaded non-core texture with texture alias \"{}\" successfully", alias);
            }
            success = true;
        } catch(const error::exception& error) {
            if(textures.at(alias)) {
                triggerError(GH::error::codes::CORE_RESOURCE_ERROR, error);
            } else {
                triggerError(GH::error::codes::RESOURCE_ERROR, error);
            }
            success = false;
        }
    }

    void unloadAllTextures() {
        for(const std::pair<std::string, bool>& texture : textures) {
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
        textures.clear();
        success = true;
    }

    std::string getTextureData(const std::string& alias) {
        if(textures.find(alias) == textures.end()) {
            error::triggerError(error::codes::RESOURCE_ERROR, error::exception("Alias \"" + alias + "\" not registered (if you registered the texture alias in any way other than the \"GH::renderer::loadTexture()\" function, that may be the cause of this error)"));
            success = false;
            return 0;
        }
        try {
            std::string result = internal::g_textureManager.getData(alias);
            if(textures.at(alias)) {
                ::userLogger.get()->trace("Read data from core texture with texture alias \"{}\" successfully", alias);
            } else {
                ::userLogger.get()->trace("Read data from non-core texture with texture alias \"{}\" successfully", alias);
            }
            success = true;
            return result;
        } catch(const error::exception& error) {
            if(textures.at(alias)) {
                triggerError(GH::error::codes::CORE_RESOURCE_ERROR, error);
            } else {
                triggerError(GH::error::codes::RESOURCE_ERROR, error);
            }
            success = false;
            return nullptr;
        }
    }

    unsigned char* const getRawTextureData(const std::string& alias) {
        if(textures.find(alias) == textures.end()) {
            error::triggerError(error::codes::RESOURCE_ERROR, error::exception("Alias \"" + alias + "\" not registered (if you registered the texture alias in any way other than the \"GH::renderer::loadTexture()\" function, that may be the cause of this error)"));
            success = false;
            return 0;
        }
        try {
            unsigned char* result = internal::g_textureManager.getRawData(alias);
            if(textures.at(alias)) {
                ::userLogger.get()->trace("Read raw data from core texture with texture alias \"{}\" successfully", alias);
            } else {
                ::userLogger.get()->trace("Read raw data from non-core texture with texture alias \"{}\" successfully", alias);
            }
            success = true;
            return result;
        } catch(const error::exception& error) {
            if(textures.at(alias)) {
                triggerError(GH::error::codes::CORE_RESOURCE_ERROR, error);
            } else {
                triggerError(GH::error::codes::RESOURCE_ERROR, error);
            }
            success = false;
            return nullptr;
        }
    }

    int getTextureWidth(const std::string& alias) {
        if(textures.find(alias) == textures.end()) {
            error::triggerError(error::codes::RESOURCE_ERROR, error::exception("Alias \"" + alias + "\" not registered (if you registered the texture alias in any way other than the \"GH::renderer::loadTexture()\" function, that may be the cause of this error)"));
            success = false;
            return 0;
        }
        try {
            int result = internal::g_textureManager.getWidth(alias);
            if(textures.at(alias)) {
                ::userLogger.get()->trace("Read width from core texture with texture alias \"{}\" successfully", alias);
            } else {
                ::userLogger.get()->trace("Read width from non-core texture with texture alias \"{}\" successfully", alias);
            }
            success = true;
            return result;
        } catch(const error::exception& error) {
            if(textures.at(alias)) {
                triggerError(GH::error::codes::CORE_RESOURCE_ERROR, error);
            } else {
                triggerError(GH::error::codes::RESOURCE_ERROR, error);
            }
            success = false;
            return 0;
        }
    }

    int getTextureHeight(const std::string& alias) {
        if(textures.find(alias) == textures.end()) {
            error::triggerError(error::codes::RESOURCE_ERROR, error::exception("Alias \"" + alias + "\" not registered (if you registered the texture alias in any way other than the \"GH::renderer::loadTexture()\" function, that may be the cause of this error)"));
            success = false;
            return 0;
        }
        try {
            int result = internal::g_textureManager.getWidth(alias);
            if(textures.at(alias)) {
                ::userLogger.get()->trace("Read height from core texture with texture alias \"{}\" successfully", alias);
            } else {
                ::userLogger.get()->trace("Read height from non-core texture with texture alias \"{}\" successfully", alias);
            }
            success = true;
            return result;
        } catch(const error::exception& error) {
            if(textures.at(alias)) {
                triggerError(GH::error::codes::CORE_RESOURCE_ERROR, error);
            } else {
                triggerError(GH::error::codes::RESOURCE_ERROR, error);
            }
            success = false;
            return 0;
        }
    }
}
