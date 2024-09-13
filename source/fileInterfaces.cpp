#include <fileInterfaces.hpp>

#include <string>
#include <tinyfiledialogs.h>
#include <resourceManager.hpp>
#include <nlohmann/json.hpp>
#include <node.hpp>

void saveNode(nodeRef node) {
    const char* filter = "*.json";
    if(const char* file = tinyfd_saveFileDialog("Where to save project?", nullptr, 1, &filter, nullptr); file != nullptr) {
        const int length = strlen(file);

        auto hasEnding = [](std::string const & value, std::string const & ending) {
            if(ending.size() > value.size()) {
                return false;
            }
            return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
        };

        try {
            if(hasEnding(file, ".json")) {
                g_resourceManager.loadResource(file, "scene");
            } else {
                g_resourceManager.loadResource((std::string)file + ".json", "scene");
            }
            try {
                g_resourceManager.write("scene", nlohmann::to_string(node->getJSON()).c_str());
            } catch(const std::exception& exception) {
                userLogger.get()->error("[JSONParser]Failed to write to file \"{}\": {}", file, exception.what());
            }
        } catch(const std::exception& exception) {
            userLogger.get()->error("[ResourceManager]Failed to open file \"{}\": {}", file, exception.what());
        }

        try {
            g_resourceManager.unloadResource("scene");
        } catch(const std::exception& exception) {
            userLogger.get()->error("[ResourceManager]Failed to close handle \"scene\": {}", exception.what());
        }
    }
}

void loadNode(nodeRef node) {
    const char* filter = "*.json";
    if(const char* file = tinyfd_openFileDialog("Open Scene", nullptr, 1, &filter, nullptr, 0); file != nullptr) {
        try {
            g_resourceManager.loadResource("scene", file);
            try {
                nlohmann::json data = nlohmann::json::parse(g_resourceManager.getData("scene"));
                node->loadJSON(data);
            } catch(const nlohmann::json::exception& exception) {
                userLogger.get()->error("[JSONParser]Failed to parse file \"{}\": {}", file, exception.what());
            }
        } catch(const std::exception& exception) {
            userLogger.get()->error("[ResourceManager]Failed to open file \"{}\": {}", file, exception.what());
        }

        try {
            g_resourceManager.unloadResource("scene");
        } catch(const std::exception& exception) {
            userLogger.get()->error("[ResourceManager]Failed to close handle \"scene\": {}", exception.what());
        }
    }
}
