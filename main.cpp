#include <PentagramExt.hpp>
#include <random>

bool shouldClose = false;
PNT::Window window("Demo Window", 600, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
float rgb[] = {1, 0, 0};
unsigned char step = 5;

void eventListener()
{
    if(PNT::getEvent().type == SDL_EVENT_KEY_DOWN)
    {
        switch(PNT::getEvent().key.keysym.sym)
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

        case SDLK_BACKSPACE:
            window.setPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
            break;

        case SDLK_EQUALS:
            if(step < 20) step++;
            break;

        case SDLK_MINUS:
            if(step > 1) step--;
            break;

        case SDLK_UP:
            window.setPosition(-1, window.getWindowData().y - step);
            break;

        case SDLK_DOWN:
            window.setPosition(-1, window.getWindowData().y + step);
            break;

        case SDLK_LEFT:
            window.setPosition(window.getWindowData().x - step, -1);
            break;

        case SDLK_RIGHT:
            window.setPosition(window.getWindowData().x + step, -1);
            break;
        }
        std::cout << PNT::getEvent().window.type << std::endl;
        if(PNT::getEvent().window.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
        {
            shouldClose = true;
            std::cout << shouldClose;
        }
    }
}

void startFrameListener()
{
    // Set background color.
    window.setClearColor(rgb[0], rgb[1], rgb[2]);

    // ImGui gui.
    ImGui::Begin("Demo Controls");

    ImGui::Text("Background Color: ");
    ImGui::ColorPicker3("##ColorPicker3 0", rgb, ImGuiColorEditFlags_InputRGB);

    ImGui::Text("Reposition Step: ");
    ImGui::SameLine();
    ImGui::SliderInt("##SliderInt 0", (int *)&step, 1, 20, "%d", ImGuiSliderFlags_AlwaysClamp);

    ImGui::End();
}

int main(int argc, char *argv[])
{
    // Initualizing SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Setting listeners
    window.setListener(PNT_LISTENER_FLAGS_EVENT, &eventListener);
    window.setListener(PNT_LISTENER_FLAGS_STARTFRAME, &startFrameListener);

    // App loop
    while(!shouldClose)
    {
        // Event processing
        while(PNT::pollEvent())
        {
            window.eventProcess();
        }

        // Start and end frame
        window.startFrame();
        window.endFrame();
    }
    return 0;
}
