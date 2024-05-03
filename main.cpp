#include <PentagramExt.hpp>

void eventListener();
void startFrameListener();

int main(int argc, char *argv[])
{
    // Initualizing SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Creating window
    PNT::Window window("Ghoul Engine", 1000, 800, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);

    // Setting listeners
    window.setListener(PNT_LISTENER_FLAGS_EVENT, &eventListener);
    window.setListener(PNT_LISTENER_FLAGS_STARTFRAME, &startFrameListener);

    // App loop
    bool shouldClose = false;
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

void eventListener()
{
}

void startFrameListener()
{
}
