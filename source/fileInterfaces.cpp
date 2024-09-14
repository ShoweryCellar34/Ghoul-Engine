#include <fileInterfaces.hpp>

#include <string>
#include <filesystem>
#include <tinyfiledialogs.h>
#include <resourceManager.hpp>
#include <nlohmann/json.hpp>
#include <node.hpp>

void setOpenFolder(std::string path) {
    g_openFolder = path;
    refreshTitle();
}

void saveAsNode(nodeRef node) {
    if(const char* folder = tinyfd_selectFolderDialog("Where to save project?", nullptr)) {
        try {

        } catch() {

        }
        // try {
        //     try {
        //         std::string JSONString = nlohmann::to_string(node->getJSON());
        //         g_resourceManager.write("scene", JSONString);
        //         setOpenFolder(file);
        //     } catch(const std::string& exception) {
        //         userLogger.get()->error("[JSONParser]Failed to write to file \"{}\": {}", file, exception);
        //     }
        // } catch(const std::string& exception) {
        //     userLogger.get()->error("[ResourceManager]Failed to open file \"{}\": {}", file, exception);
        // }

        // try {
        //     g_resourceManager.unloadResource("scene");
        // } catch(const std::string& exception) {
        //     userLogger.get()->error("[ResourceManager]Failed to close handle \"scene\": {}", exception);
        // }
    }
}

void saveScene(nodeRef node) {
    if(g_openFolder == "") {
        saveAsNode(node);
    } else {
        try {
            g_resourceManager.loadResource("scene", g_openFolder);
            try {
                std::string JSONString = nlohmann::to_string(node->getJSON());
                g_resourceManager.write("scene", JSONString);
            } catch(const std::string& exception) {
                userLogger.get()->error("[JSONParser]Failed to write to file \"{}\": {}", g_openFolder.string(), exception);
            }
        } catch(const std::string& exception) {
            userLogger.get()->error("[ResourceManager]Failed to open file \"{}\": {}", g_openFolder.string(), exception);
        }

        try {
            g_resourceManager.unloadResource("scene");
        } catch(const std::string& exception) {
            userLogger.get()->error("[ResourceManager]Failed to close handle \"scene\": {}", exception);
        }
    }
}

void loadProject(nodeRef node) {
    const char* filter = "*.json";
    if(const char* file = tinyfd_openFileDialog("Open Scene", nullptr, 1, &filter, nullptr, 0); file != nullptr) {
        try {
            g_resourceManager.loadResource("scene", file);
            try {
                nlohmann::json data = nlohmann::json::parse(g_resourceManager.getData("scene"));
                node->loadJSON(data);
                setOpenFolder(file);
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
