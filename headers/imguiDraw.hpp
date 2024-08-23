#pragma once

#include <memory>
#include <defines.hpp>

namespace PNT {
    class Window;
}

struct scene;

void drawGlobalDockingWindow(const PNT::Window& window);

struct node;

void drawNodeTree(const PNT::Window& window, nodeRef currentScene);

void drawNodeInspector(const PNT::Window& window, nodeRef currentScene);
