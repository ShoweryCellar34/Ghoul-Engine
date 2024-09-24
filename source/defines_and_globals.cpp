#include <defines_and_globals.hpp>

#include <Pentagram.hpp>

PNT::Window g_window;
fs::path g_openFile;
std::string g_projectName = "Unnamed Project";
std::vector<nodeRef> g_scenes;
nodeRef g_currentScene = nullptr;
nlohmann::json g_nodeClipboard;

void refreshTitle() {
    std::string title;
    if(g_projectName != "") {
        title += g_projectName + " | Ghoul Engine";
    } else {
        title = "Unnamed Project | Ghoul Engine";
    }

    g_window.setTitle(title);
}
