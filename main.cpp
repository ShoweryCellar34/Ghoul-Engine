#include <PentagramExt.hpp>

bool shouldClose = false;
void eventListener(PNT::Window *window);
void startFrameListener(PNT::Window *window);

int main(int argc, char *argv[]) {
    // Initualizing SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Creating window
    PNT::Window window("Ghoul Engine", 1000, 800, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);

    // Setting listeners
    window.setListener(PNT_LISTENER_FLAGS_KEYBOARDEVENT, &eventListener);
    window.setListener(PNT_LISTENER_FLAGS_MOUSEEVENT, &eventListener);
    window.setListener(PNT_LISTENER_FLAGS_STARTFRAME, &startFrameListener);

    // App loop
    while(!shouldClose) {
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

void eventListener(PNT::Window *window) {
    switch(PNT::getEvent().key.keysym.sym) {
        case SDLK_1:
            window->setClearColor(1.0f, 0.0f, 0.0f);
            break;

        case SDLK_2:
            window->setClearColor(0.0f, 0.0f, 1.0f);
            break;

        case SDLK_3:
            window->setClearColor(0.0f, 0.0f, 0.0f);
            break;
    }
    if(PNT::getEvent().window.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) shouldClose = true;
}

void startFrameListener(PNT::Window *window) {
    ImGui::ShowDemoWindow();
}
