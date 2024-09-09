#pragma once

#include <memory>
#include <defines_and_globals.hpp>

namespace PNT {
    class Window;
}

void drawGlobalDockingWindow(const PNT::Window& window);

void drawMainMenuBar();

struct node;

void drawNodeTree(const PNT::Window& window, nodeRef currentScene);

void drawNodeInspector(const PNT::Window& window, nodeRef currentScene);
