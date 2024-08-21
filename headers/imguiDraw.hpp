#pragma once

#include <memory>

namespace PNT {
    class Window;
}

struct scene;

void drawGlobalDockingWindow(const PNT::Window& window);

struct node;

void drawNodeTree(const PNT::Window& window, std::shared_ptr<node> currentScene);

void drawNodeInspector(const PNT::Window& window, std::shared_ptr<node> currentScene);
