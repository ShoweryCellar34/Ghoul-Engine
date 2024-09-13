#include <fileInterfaces.hpp>

#include <tinyfiledialogs.h>
#include <resourceManager.hpp>
#include <nlohmann/json.hpp>
#include <node.hpp>

void saveNode(nodeRef node) {
    const char* filter = "*.json";
    if(const char* file = tinyfd_saveFileDialog("Where to save project?", nullptr, 1, &filter, nullptr); file != nullptr) {
        g_resourceManager.loadResource(file, "json");
        g_resourceManager.write("json", nlohmann::to_string(node->getJSON()).c_str());
        g_resourceManager.unloadResource("json");
    }
}
