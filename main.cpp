#include <PentagramExt.hpp>
#include <random>

unsigned short rb[] = {255, 0};

void testCallback(SDL_Event event)
{
    switch(event.key.keysym.sym)
    {
    case SDLK_1:
        rb[0] = 255;
        rb[1] = 0;
        break;

    case SDLK_2:
        rb[0] = 0;
        rb[1] = 255;
        break;
    }
}

int main(int argc, char *argv[])
{
    PNT::Window test("test", 500, 500, SDL_WINDOW_RESIZABLE);
    //PNT::Window test2("test2", 500, 500, SDL_WINDOW_RESIZABLE);
    test.setEventCallback(testCallback);
    bool shouldClose = true;
    while(!shouldClose)
    {
        while(SDL_PollEvent(&PNT::Window::event))
        {
            test.startFrame(rb[0], 0, rb[1]);
            test.eventProcess(&shouldClose);
            ImGui::Begin("Test");
            ImGui::End();
            test.endFrame();
            //test2.startFrame();
            //test2.eventProcess();
            //test2.endFrame();
        }
    }
    return 0;
}
