#include <PentagramExt.hpp>
#include <random>

float rgb[] = {1, 0, 0};

void testCallback(SDL_Event event)
{
    switch(event.key.keysym.sym)
    {
    case SDLK_1:
        rgb[0] = 1;
        rgb[1] = 0;
        rgb[2] = 0;
        break;

    case SDLK_2:
        rgb[0] = 0;
        rgb[1] = 0;
        rgb[2] = 1;
        break;
    }
}

int main(int argc, char *argv[])
{
    PNT::Window window("Demo window", 500, 500, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    window.setEventCallback(&testCallback);
    bool shouldClose = false;
    while(!shouldClose)
    {
        // Event processing
        while(SDL_PollEvent(&PNT::Window::event))
        {
            window.eventProcess(shouldClose);
        }

        // Begin frame
        window.startFrame(rgb[0]*255, rgb[1]*255, rgb[2]*255);

        // ImGui
        ImGui::Begin("Controls");

        ImGui::Text("Background Color: ");
        ImGui::ColorPicker3("##ColorPicker3 0", rgb, ImGuiColorEditFlags_InputRGB);

        ImGui::End();

        // End frame
        window.endFrame();
    }
    return 0;
}
