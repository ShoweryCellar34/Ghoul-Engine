#include <PentagramExt.hpp>
#include <random>

float rgb[] = {1, 0, 0};

void testCallback(PNT::Window *window, SDL_Event event)
{
    static unsigned short step = 1;
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

    case SDLK_BACKSPACE:
        window->setPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        break;

    case SDLK_EQUALS:
        step++;
        break;

    case SDLK_MINUS:
        step--;
        break;

    case SDLK_UP:
        window->setPosition(-1, window->getPosition().second - step);
        break;

    case SDLK_DOWN:
        window->setPosition(-1, window->getPosition().second + step);
        break;

    case SDLK_LEFT:
        window->setPosition(window->getPosition().first - step, -1);
        break;

    case SDLK_RIGHT:
        window->setPosition(window->getPosition().first + step, -1);
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
        window.setClearColor(rgb[0], rgb[1], rgb[2]);
        window.startFrame();

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
