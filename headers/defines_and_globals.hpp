#pragma once

#include <cstddef>
#include <filesystem>
#include <string>
#include <vector>
#include <Pentagram.hpp>
#include <nlohmann/json.hpp>

namespace GH {
    namespace textureIDList {
        inline size_t edit = 0, exit = 0, maximize = 0, minimize = 0, iconify = 0;
    }

    enum class RENAME_STATUS : int {
        CANCLED,
        SUCCESS
    };

    struct node;
    typedef node* nodeRef;

    namespace fs = std::filesystem;
    class resourceManager;
    extern resourceManager g_resourceManager;

    inline PNT::Window g_window;
    inline bool g_windowMaxed = false;
    inline size_t g_prevWidth = 0;
    inline size_t g_prevHeight = 0;
    inline fs::path g_openFile;
    inline std::string g_projectName = "Unnamed Project";
    inline std::vector<nodeRef> g_scenes;
    inline nodeRef g_currentScene = nullptr;
    inline nlohmann::json g_nodeClipboard;

    void refreshTitle();
    size_t newID();
    std::string newIDstr();
    size_t newFrameID();
    std::string newFrameIDstr();
    void clearFrameIDs();
}
