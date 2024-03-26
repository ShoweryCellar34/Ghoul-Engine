#include <PentagramExt.hpp>

int main(int argc, char *argv[])
{
    PNT::initialize(800, 500, "Ghoul Engine");
    PNT::vsync(PNT_VSYNC_ON);
    bool running = true;
    while(running)
    {
        SDL_Event event = PNT::startFrame(&running);
        ImGui::ShowDemoWindow();
        PNT::endFrame();
    }
    PNT::deinitialize();
    return 0;
}
