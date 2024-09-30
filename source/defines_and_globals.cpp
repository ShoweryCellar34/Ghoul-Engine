#include <defines_and_globals.hpp>

#include <Pentagram.hpp>

void refreshTitle() {
    std::string title;
    if(g_projectName != "") {
        title += g_projectName + " | Ghoul Engine";
    } else {
        title = "Unnamed Project | Ghoul Engine";
    }

    g_window.setTitle(title);
}
