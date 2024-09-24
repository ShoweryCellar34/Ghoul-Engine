#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

struct treeNode;
typedef treeNode* nodeRef;

namespace fs = std::filesystem;
class resourceManager;
extern resourceManager g_resourceManager;

namespace PNT {
    class Window;
}
extern PNT::Window g_window;
extern fs::path g_openFile;
extern std::string g_projectName;
extern std::vector<nodeRef> g_scenes;
extern nodeRef g_currentScene;
extern nlohmann::json g_nodeClipboard;

extern void refreshTitle();
