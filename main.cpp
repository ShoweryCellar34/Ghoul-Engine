#include <PentagramExt.hpp>
#include <windows.hpp>
#include <random>

int main(int argc, char *argv[])
{
    PNT::initialize(800, 500, "Ghoul Engine");
    PNT::vsync(PNT_VSYNC_ON);
    PNT::Window test("test", 500, 500, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    PNT::Window test2("test2", 500, 500, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    bool running = true;
    while(running)
    {
        test.startFrame(127, 127, 127);
        test.eventProcess();
        test.endFrame();
        test2.startFrame(100, 50, 200);
        test2.eventProcess();
        test2.endFrame();
        static unsigned short rgba[8];
        static bool rgbaRondomize = false;
        SDL_Event event = PNT::startFrame(&running, rgba[0], rgba[2], rgba[4], rgba[6]);
        ImGui::Begin("Rehehehehehehehe");

        ImGui::Text("Backgroung RGBA: ");
        ImGui::SameLine();
        ImGui::SliderInt4("##SliderInt4 0", (int *)rgba, 0, 255, "%d", ImGuiSliderFlags_AlwaysClamp);

        ImGui::Text("Backgroung RGBA Randomize (flashing lights): ");
        ImGui::SameLine();
        ImGui::Checkbox("##Checkbox 0", &rgbaRondomize);
        if(rgbaRondomize)
        {
            rgba[0] = rand() % 255 + 1;
            rgba[2] = rand() % 255 + 1;
            rgba[4] = rand() % 255 + 1;
            rgba[6] = rand() % 255 + 1;
        }

        ImGui::End();
        PNT::endFrame();
    }
    PNT::deinitialize();
    return 0;
}
