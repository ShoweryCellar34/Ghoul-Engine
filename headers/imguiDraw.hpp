#pragma once

#include <string>
#include <defines_and_globals.hpp>

namespace GH {
    RENAME_STATUS drawRenameWindow(bool* renaming, std::string* output, std::string* buffer, std::string title);
    RENAME_STATUS drawRenameWindow(bool* renaming,  void(*output)(std::string), std::string* buffer, std::string title);
    void drawGlobalDockingWindow();
    void drawMainMenuBar();
    void drawNodeTree();
    void drawNodeInspector();
}
