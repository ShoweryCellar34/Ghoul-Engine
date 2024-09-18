#include <fileInterfaces.hpp>

#include <string>
#include <filesystem>
#include <tinyfiledialogs.h>
#include <resourceManager.hpp>
#include <nlohmann/json.hpp>
#include <node.hpp>

void setOpenFile(std::string path) {
    g_openFile = path;
    refreshTitle();
}

void saveAs() {
    const char* filter = "*.json";
    if(const char* file = tinyfd_saveFileDialog("Where to save project?", nullptr, 1, &filter, nullptr)) {
        try {
            g_resourceManager.loadResource("scene", file);
            try {
                nlohmann::json json;
                json["name"] = g_projectName;

                nlohmann::json scenes = nlohmann::json::array();
                for(nodeRef child : g_scenes) {
                    scenes.push_back(child->getJSON());
                }
                json["scenes"] = scenes;

                g_resourceManager.write("scene", nlohmann::to_string(json));
                setOpenFile(file);
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

void saveScene() {
    if(g_openFile == "") {
        g_projectName = "Unnamed Project";
        saveAs();
    } else {
        try {
            g_resourceManager.loadResource("scene", g_openFile);
            try {
                nlohmann::json json;
                json["name"] = g_projectName;

                nlohmann::json scenes = nlohmann::json::array();
                for(nodeRef child : g_scenes) {
                    scenes.push_back(child->getJSON());
                }
                json["scenes"] = scenes;

                g_resourceManager.write("scene", nlohmann::to_string(json));
            } catch(const std::string& exception) {
                userLogger.get()->error("[JSONParser]Failed to write to file \"{}\": {}", g_openFile.string(), exception);
            }
        } catch(const std::string& exception) {
            userLogger.get()->error("[ResourceManager]Failed to open file \"{}\": {}", g_openFile.string(), exception);
        }

        try {
            g_resourceManager.unloadResource("scene");
        } catch(const std::string& exception) {
            userLogger.get()->error("[ResourceManager]Failed to close handle \"scene\": {}", exception);
        }
    }
}

void loadProject() {
    const char* filter = "*.json";
    if(const char* file = tinyfd_openFileDialog("Open Scene", nullptr, 1, &filter, nullptr, 0); file != nullptr) {
        try {
            g_resourceManager.loadResource("scene", file);
            try {
                nlohmann::json json = nlohmann::json::parse(g_resourceManager.getData("scene"));
                g_projectName = json["name"];

                g_currentScene = nullptr;
                for(nodeRef scene : g_scenes) {
                    delete scene;
                }
                g_scenes.clear();
                if(json.contains("scenes") && json["scenes"].is_array()) {
                    for (const auto& sceneJson : json.at("scenes")) {
                        nodeRef childNode = new treeNode(nullptr, nullptr, sceneJson);
                        g_scenes.push_back(childNode);
                        g_currentScene = childNode;
                    }
                }
                setOpenFile(file);
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
