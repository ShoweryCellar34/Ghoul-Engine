#include "include/GLAD/glad.h"
#include "include/IMGUI/imgui.h"
#include "include/IMGUI/imgui_stdlib.h"
#include "include/IMGUI/imgui_impl_sdl2.h"
#include "include/IMGUI/imgui_impl_opengl3.h"
#include <iostream>
#include "include/SDL2/SDL.h"

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        return -1;
    }

    std::string windowTitle = "Dear ImGui SDL2 + OpenGL3 example";
    SDL_DisplayMode displayMode;
    SDL_GetDesktopDisplayMode(0, &displayMode);
    int windowWidth = displayMode.w / 2;
    int windowHeight = displayMode.h / 2;

    const char *glsl_version = "#version 460";

    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window *window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, windowFlags);
    SDL_GLContext openglContext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, openglContext);
    SDL_GL_SetSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, openglContext);
    ImGui_ImplOpenGL3_Init(glsl_version);


    // Setup


    // Variables


    bool running = true;
    while (running)
    {
        glClearColor(255, 255, 255, 255);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();


        // ImGui
        ImGui::ShowDemoWindow();


        // Render


        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(openglContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
