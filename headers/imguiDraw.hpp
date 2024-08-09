#pragma once

namespace PNT {
    class Window;
}

struct scene;

void drawGlobalDockingWindow(const PNT::Window& window);

struct node;

void drawNodeTree(const PNT::Window& window, scene* currentScene);

void drawNodeInspector(const PNT::Window& window, scene* currentScene);
