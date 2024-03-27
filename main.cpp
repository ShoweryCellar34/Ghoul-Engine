#include <PentagramExt.hpp>

int main(int argc, char *argv[])
{
    PNT::initialize(800, 500, "Ghoul Engine");
    PNT::vsync(PNT_VSYNC_ON);
    bool running = true;
    while(running)
    {
        static unsigned short rgba[8];
        SDL_Event event = PNT::startFrame(&running, rgba[0], rgba[2], rgba[4], rgba[6]);
        ImGui::Begin("Background Color");
        ImGui::Text("RGBA: ");
        ImGui::SameLine();
        ImGui::SliderInt4("##SliderInt4 0", (int *)rgba, 0, 255, "%d", ImGuiSliderFlags_AlwaysClamp);
        ImGui::End();
        PNT::endFrame();
    }
    PNT::deinitialize();
    return 0;
}
