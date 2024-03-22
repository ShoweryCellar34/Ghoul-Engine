#include <PentagramExt.hpp>

int main(int argc, char *argv[])
{
    PNT::initialize(800, 500, "Ghoul Engine");
    PNT::vsync(PNT::ON);
    bool running = true;
    while(running)
    {
        SDL_Event event = PNT::startFrame(&running);
        while (SDL_PollEvent(&event))
        {
            if(event.type = SDL_EVENT_QUIT)
            {
                running = false;
            }
        }
        ImGui::ShowDemoWindow();
        PNT::endFrame();
    }
    return 0;
}
