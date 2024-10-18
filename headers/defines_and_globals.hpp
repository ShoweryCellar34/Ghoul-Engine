#pragma once

#include <cstddef>
#include <filesystem>
#include <string>
#include <vector>
#include <Pentagram.hpp>
#include <nlohmann/json.hpp>
#include <resourceManager.hpp>

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

    inline resourceManager g_resourceManager;

    inline PNT::Window g_window;
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
