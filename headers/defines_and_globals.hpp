#pragma once

#include <array>
#include <cstddef>
#include <filesystem>
#include <string>
#include <vector>
#include <Pentagram.hpp>
#include <nlohmann/json.hpp>
#include <texture.hpp>
#include <resourceManager.hpp>

namespace GH {
    inline std::array<texture, 1> g_UITextures;

    namespace UITextureIDs {
        inline int edit = 0;
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

    void copyNode();
    void cutNode();
    void pasteNode();
    void copyNode(nodeRef target);
    void cutNode(nodeRef target);
    void pasteNode(nodeRef target);

    void refreshTitle();
    size_t newID();
    std::string newIDstr();
    size_t newFrameID();
    std::string newFrameIDstr();
    void clearFrameIDs();

    void loadUITextures();
}
