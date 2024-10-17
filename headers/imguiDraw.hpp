#pragma once

#include <string>
#include <defines_and_globals.hpp>

namespace GH {
    RENAME_STATUS drawRenameWindow(std::string& output, const std::string& title);
    RENAME_STATUS drawRenameWindow(void(*output)(std::string), std::string title);
    void drawGlobalDockingWindow();
    void drawMainMenuBar();
    void drawNodeTree();
    void drawNodeInspector();
}
