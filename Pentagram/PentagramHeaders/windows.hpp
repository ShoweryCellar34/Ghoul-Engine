#pragma once

#include <includes.hpp>
#include <logger.hpp>
#include <enumerations.hpp>
#include <utilities/ptrToChar.hpp>

namespace PNT
{
    class Window
    {
    private:
        // SDL data
        SDL_Window *window = nullptr;
        SDL_GLContext openglContext = nullptr;

        // ImGui data
        ImGuiContext *ImGuiContext = nullptr;
        ImGuiIO io;
        const char *glsl_version = "#version 460";
    public:
        // Window data
        char *title = new char[0];
        unsigned short width = 0, height = 0;
        int x = 0, y = 0;
        bool hidden = true;
        unsigned char windowID = 0;
        float rgba[4] = {255.0f,  255.0f, 255.0f, 255.0f};
        char vsyncMode = 0;

        // other data
        static inline int instances;
        double deltaTime = 0;

        // listener data
        void (*startFrameListener)();
        void (*endFrameListener)();
        void (*eventListener)();
    public:
    // The global event for all windows.
        static inline SDL_Event event = SDL_Event();

        // Sets the title of the window, returns the sdl error code (0 is success).
        int setTitle(const char *newTitle)
        {
            int errorCode = 0;
            ptrToChar(title, newTitle);
            errorCode = SDL_SetWindowTitle(window, newTitle);
            if(errorCode != 0)
            {
                log.log(2, SDL_GetError());
            }
            return errorCode;
        }

        // Sets the width and height of the window (-1 = unchanged), returns the sdl error code (0 is success).
        int setDimentions(unsigned short newWidth, unsigned short newHeight)
        {
            int errorCode = 0;
            errorCode = SDL_SetWindowSize(window, newWidth == -1 ? width : newWidth, newHeight == -1 ? height : newHeight);
            if(errorCode != 0)
            {
                log.log(2, SDL_GetError());
            }
            return errorCode;
        }

        // Sets the x and y coordinates of the window (-1 = unchanged), returns the sdl error code (0 is success).
        int setPosition(int newX, int newY)
        {
            int errorCode = 0;
            errorCode = SDL_SetWindowPosition(window, newX == -1 ? x : newX, newY == -1 ? y : newY);
            if(errorCode != 0)
            {
                log.log(2, SDL_GetError());
            }
            return errorCode;
        }

        // Shows the window, returns the sdl error code (0 is success).
        int show()
        {
            int errorCode = 0;
            errorCode = SDL_RaiseWindow(window);
            if(errorCode != 0)
            {
                log.log(2, SDL_GetError());
            }
            return errorCode;
        }

        // Hides the window, returns the sdl error code (0 is success).
        int hide()
        {
            int errorCode = 0;
            errorCode = SDL_HideWindow(window);
            if(errorCode != 0)
            {
                log.log(2, SDL_GetError());
            }
            return errorCode;
        }

        // Sets the vsync mode of the window (0 = off, 1 = on, -1 = adaptive), returns the sdl error code (0 is success).
        int vsync(char newVsyncMode)
        {
            int errorCode;
            vsyncMode = newVsyncMode;
            errorCode = SDL_GL_SetSwapInterval(vsyncMode);
            if(errorCode != 0)
            {
                log.log(2, SDL_GetError());
            }
            return errorCode;
        }

        // Sets the opengl clear color for the window (-1 = unchanged).
        void setClearColor(float red = -1, float green = -1, float blue = -1, float alpha = -1)
        {
            if(red != -1) rgba[0] = red;
            if(green != -1) rgba[1] = green;
            if(blue != -1) rgba[2] = blue;
            if(alpha != -1) rgba[3] = alpha;
        }

        // Sets the listener for the specified event (use nullptr to clear listener).
        void setListener(unsigned char listenerID, void (*newListener)())
        {
            switch(listenerID)
            {
            case PNT_LISTENER_FLAGS_EVENT:
                eventListener = newListener;
                break;

        	case PNT_LISTENER_FLAGS_STARTFRAME:
                startFrameListener = newListener;
                break;

            case PNT_LISTENER_FLAGS_ENDFRAME:
                endFrameListener = newListener;
                break;

            default:
                break;
            }
        }

        // Starts the opengl and imgui frames for the window, returns the sdl error code (0 is success)..
        int startFrame()
        {
            int errorCode = 0;
            errorCode = SDL_GL_MakeCurrent(window, openglContext);
            if(errorCode != 0)
            {
                log.log(2, SDL_GetError());
                return errorCode;
            }
            glClearColor(rgba[0], rgba[1], rgba[2], rgba[3]);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui::SetCurrentContext(ImGuiContext);
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();
            if(startFrameListener != nullptr)
            {
                startFrameListener();
            }
            return errorCode;
        }

        // Hides the window, returns the sdl error code (0 is success). 
        int endFrame()
        {
            int errorCode = 0;
            ImGui::Render();
            glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            errorCode = SDL_GL_SwapWindow(window);
            if(errorCode != 0)
            {
                log.log(2, SDL_GetError());
            }
            if(endFrameListener != nullptr)
            {
                endFrameListener();
            }
            return errorCode;
        }

        /* Processes the current event, listener functionality supported (check setEventlistener() function for details),
        takes a boolean as a parameter setting it to true if a close request was detected for the window.*/
        void eventProcess(bool *shouldClose)
        {
            if(event.window.windowID == windowID)
            {
                ImGui_ImplSDL3_ProcessEvent(&event);
                switch(event.window.type)
                {
                case SDL_EVENT_WINDOW_RESIZED:
                    width = event.window.data1;
                    height = event.window.data2;
                    break;

                case SDL_EVENT_WINDOW_SHOWN:
                    hidden = true;
                    break;

                case SDL_EVENT_WINDOW_HIDDEN:
                    hidden = false;
                    break;

                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    *shouldClose = true;
                    break;

                case SDL_EVENT_WINDOW_MOVED:
                    x = event.window.data1;
                    y = event.window.data2;
                    break;

                default:
                    break;
                }
                if(eventListener != nullptr)
                {
                    eventListener();
                }
            }
        }

        // Constructor/Destructor
        Window(const char *windowTitle = "Title", int windowWidth = 600, int windowHeight = 600, SDL_WindowFlags windowFlags = SDL_WINDOW_OPENGL)
        {
            instances++;
            ptrToChar(title, windowTitle);
            width = windowWidth;
            height = windowHeight;
            window = SDL_CreateWindow(title, width, height, windowFlags | SDL_WINDOW_OPENGL);
            unsigned char currentDisplay = SDL_GetDisplayForWindow(window);
            SDL_SetWindowPosition(window, (SDL_GetCurrentDisplayMode(currentDisplay)->w / 2) - (width / 2), (SDL_GetCurrentDisplayMode(currentDisplay)->h / 2) - (height / 2) + 1);
            windowID = SDL_GetWindowID(window);

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            openglContext = SDL_GL_CreateContext(window);
            gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

            ImGuiContext = ImGui::CreateContext();
            ImGui::SetCurrentContext(ImGuiContext);
            ImGui_ImplSDL3_InitForOpenGL(window, openglContext);
            ImGui_ImplOpenGL3_Init(glsl_version);
            io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
            ImGui::StyleColorsDark();
        }
        ~Window()
        {
            ImGui::SetCurrentContext(ImGuiContext);
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplSDL3_Shutdown();
            ImGui::DestroyContext(ImGuiContext);

            SDL_GL_DeleteContext(openglContext);

            SDL_DestroyWindow(window);
            delete[] title;
        }
    };
}
