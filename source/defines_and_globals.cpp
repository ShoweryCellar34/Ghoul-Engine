#include <defines_and_globals.hpp>

#include <Pentagram.hpp>

namespace GH {
    void refreshTitle() {
        std::string title;
        title += g_projectName + " | Ghoul Engine";

        g_window.setTitle(title);
    }
}
