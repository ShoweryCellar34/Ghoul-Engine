#include <fileInterfaces.hpp>

#include <string>
#include <tinyfiledialogs.h>
#include <resourceManager.hpp>
#include <nlohmann/json.hpp>
#include <node.hpp>

// OpenFile definition

std::string g_openPath = "";

void saveAsNode(nodeRef node) {
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
                g_resourceManager.loadResource("scene", file);
            } else {
                g_resourceManager.loadResource((std::string)file + ".json", "scene");
            }
            try {
                g_resourceManager.write("scene", nlohmann::to_string(node->getJSON()));
                g_openPath = file;
            } catch(const std::string& exception) {
                userLogger.get()->error("[JSONParser]Failed to write to file \"{}\": {}", file, exception);
            }
        } catch(const std::string& exception) {
            userLogger.get()->error("[ResourceManager]Failed to open file \"{}\": {}", file, exception);
        }

        try {
            g_resourceManager.unloadResource("scene");
        } catch(const std::string& exception) {
            userLogger.get()->error("[ResourceManager]Failed to close handle \"scene\": {}", exception);
        }
    }
}

void saveNode(nodeRef node) {
    if(g_openPath == "") {
        saveAsNode(node);
    } else {
        try {
            g_resourceManager.loadResource("scene", g_openPath);
            try {
                g_resourceManager.write("scene", nlohmann::to_string(node->getJSON()));
            } catch(const std::string& exception) {
                userLogger.get()->error("[JSONParser]Failed to write to file \"{}\": {}", g_openPath, exception);
            }
        } catch(const std::string& exception) {
            userLogger.get()->error("[ResourceManager]Failed to open file \"{}\": {}", g_openPath, exception);
        }

        try {
            g_resourceManager.unloadResource("scene");
        } catch(const std::string& exception) {
            userLogger.get()->error("[ResourceManager]Failed to close handle \"scene\": {}", exception);
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
                g_openPath = file;
            } catch(const nlohmann::json::exception& exception) {
                userLogger.get()->error("[JSONParser]Failed to parse file \"{}\": {}", file, exception.what());
            }
        } catch(const std::string& exception) {
            userLogger.get()->error("[ResourceManager]Failed to open file \"{}\": {}", file, exception);
        }

        try {
            g_resourceManager.unloadResource("scene");
        } catch(const std::string& exception) {
            userLogger.get()->error("[ResourceManager]Failed to close handle \"scene\": {}", exception);
        }
    }
}
