#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <Pentagram.hpp>
#include <nlohmann/json.hpp>

enum class RENAME_STATUS : int {
    AWATING,
    CANCLED,
    SUCCESS
};

struct treeNode;
typedef treeNode* nodeRef;

namespace fs = std::filesystem;
class resourceManager;
extern resourceManager g_resourceManager;

inline PNT::Window g_window;
inline fs::path g_openFile;
inline std::string g_projectName = "Unnamed Project";
inline std::vector<nodeRef> g_scenes;
inline nodeRef g_currentScene = nullptr;
inline nlohmann::json g_nodeClipboard;

void refreshTitle();
