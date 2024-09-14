#include <fileInterfaces.hpp>

#include <string>
#include <tinyfiledialogs.h>
#include <resourceManager.hpp>
#include <nlohmann/json.hpp>
#include <node.hpp>

void saveNode(nodeRef node) {
    const char* filter = "*.json";
    if(const char* file = tinyfd_saveFileDialog("Where to save project?", nullptr, 1, &filter, nullptr); file != nullptr) {
        const int len = strlen(file);

        auto hasEnding = [](std::string const & value, std::string const & ending) {
            if(ending.size() > value.size()) {
                return false;
            }
            return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
        };

        if(hasEnding(file, ".json")) {
            g_resourceManager.loadResource(file, "json");
        } else {
            g_resourceManager.loadResource((std::string)file + ".json", "json");
        }
        g_resourceManager.write("json", nlohmann::to_string(node->getJSON()).c_str());
        g_resourceManager.unloadResource("json");
    }
}
