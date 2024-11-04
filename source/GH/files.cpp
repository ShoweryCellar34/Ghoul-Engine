#include <GH/files.hpp>

#include <PNT/Pentagram.hpp>
#include <GH/globalsAndDefines.hpp>
#include <GH/error.hpp>

namespace GH {
    bool loadResource(const fs::path& path, const std::string& desiredAlias, bool isCore) {
        try {
            g_resourceManager.loadResource(desiredAlias, (fs::path)GH::g_gameFolder / path);
            if(isCore) {
                ::userLogger.get()->info("Loaded core resource at path \"{}\" with alias \"{}\" successfully", path.string(), desiredAlias);
            } else {
                ::userLogger.get()->info("Loaded resource at path \"{}\" with alias \"{}\" successfully", path.string(), desiredAlias);
            }
            return true;
        } catch(const std::exception& error) {
            if(isCore) {
                triggerError(GH::errors::CORE_RESOURCE_ERROR, path.string());
            } else {
                triggerError(GH::errors::RESOURCE_ERROR, path.string());
            }
            return false;
        }
    }
}
