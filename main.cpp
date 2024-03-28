#include <PentagramExt.hpp>

int main(int argc, char *argv[])
{
    PNT::initialize(800, 500, "Ghoul Engine");
    PNT::vsync(PNT_VSYNC_ON);
    bool running = true;
    while(running)
    {
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
