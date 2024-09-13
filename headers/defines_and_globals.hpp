#pragma once

#include <string>

namespace PNT {
    class Window;
}
extern PNT::Window g_window;

struct node;
typedef node* nodeRef;

class resourceManager;
extern resourceManager g_resourceManager;

extern std::string g_openPath;
