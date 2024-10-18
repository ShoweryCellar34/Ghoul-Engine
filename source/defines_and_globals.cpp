#include <defines_and_globals.hpp>

#include <Pentagram.hpp>

namespace GH {
    void refreshTitle() {
        std::string title;
        title += g_projectName + " | Ghoul Engine";

        g_window.setTitle(title);
    }

    ::size_t counter = 0;
    size_t newID() {
        return counter++;
    }

    std::string newIDstr() {
        return std::to_string(counter++);
    }

    ::size_t frameIDs = 0;
    size_t newFrameID() {
        return frameIDs++;
    }

    std::string newFrameIDstr() {
        return std::to_string(frameIDs++);
    }

    void clearFrameIDs() {
        frameIDs = 0;
    }
}
