#include <defines_and_globals.hpp>

#include <Pentagram.hpp>
#include <resourceManager.hpp>
#include <texture.hpp>

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

    void loadUITextures() {
        g_resourceManager.loadResource("editIcon", "./res/textures/icons/edit.png");
        std::string editIconData = g_resourceManager.getData("editIcon");
        UITextures[0].setGL(g_window.getGL());
        UITextures[0].setData(editIconData);
        UITextures[0].load();
        UITextureIDs::edit = UITextures[0].getID();
    }
}
