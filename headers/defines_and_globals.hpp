#pragma once

#include <filesystem>
#include <string>

struct node;
typedef node* nodeRef;

namespace fs = std::filesystem;
class resourceManager;
extern resourceManager g_resourceManager;

namespace PNT {
    class Window;
}
extern PNT::Window g_window;
extern fs::path g_openFile;

extern void refreshTitle();

