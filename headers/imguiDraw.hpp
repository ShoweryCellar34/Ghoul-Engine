#pragma once

#include <string>
#include <defines_and_globals.hpp>

int drawRenameWindow(bool* renaming, std::string* output, std::string* buffer, std::string title);
int drawRenameWindow(bool* renaming,  void(*output)(std::string), std::string* buffer, std::string title);
void drawGlobalDockingWindow();
void drawMainMenuBar();
void drawNodeTree(const nodeRef currentScene);
void drawNodeInspector(const nodeRef currentScene);
