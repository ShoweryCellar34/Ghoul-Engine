#pragma once

namespace PNT {
    class Window;
}

void drawGlobalDockingWindow(const PNT::Window& window);

struct node;

void drawNodeTree(const PNT::Window& window, const node& node);

void drawNodeInspector(const PNT::Window& window);
