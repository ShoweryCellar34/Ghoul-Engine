#include "include/GLAD/glad.h"
#include "include/IMGUI/imgui.h"
#include "include/IMGUI/imgui_stdlib.h"
#include "include/IMGUI/imgui_impl_sdl2.h"
#include "include/IMGUI/imgui_impl_opengl3.h"
#include "include/SDL2/SDL.h"
#include "include/stb/stb_image.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


class Logger
{
    private:
        std::ofstream logFile;
        std::string tempBuffer;
        void log(std::string prefix, std::string message)
        {
            if(!save)
            {
                tempBuffer.append("[NOT SAVED]");
            }
            tempBuffer.append(prefix);
            tempBuffer.append(message);
            tempBuffer.append("\n");
            if(save)
            {
                logFile.open(logFilePath, std::ios::app);
                logFile << tempBuffer;
                logFile.close();
            }
            if(print)
            {
                std::cout << tempBuffer;
            }
            tempBuffer.clear();
        }
    public:
        std::string logFilePath = "log.txt";
        bool print = true;
        bool save = true;
        void Note(std::string message)
        {
            log("[NOTE] ", message);
        }
        void Warn(std::string message)
        {
            log("[WARN] ", message);
        }
        void Error(std::string message)
        {
            log("[ERROR] ", message);
        }
        void FatalError(std::string message)
        {
            log("[FATAL ERROR] ", message);
        }
        Logger()
        {
            logFile.open(logFilePath);
            logFile.clear();
            logFile.close();
        }
        Logger(bool print, bool save)
        {
            logFile.open(logFilePath);
            logFile.clear();
            logFile.close();
            this -> print = print;
            this -> save = save;
        }
        Logger(bool print, bool save, std::string logFilePath)
        {
            logFile.open(logFilePath);
            logFile.clear();
            logFile.close();
            this -> print = print;
            this -> save = save;
            this -> logFilePath = logFilePath;
        }
};


class Shader
{
    public:
        unsigned int shaderProgram;
        Shader(const char *vertexShaderPath, const char *fragmentShaderPath, Logger &log)
        {
            std::string vertexShaderString;
            std::string fragmentShaderString;
            std::ifstream vertexShaderSource;
            std::ifstream fragmentShaderSource;
            vertexShaderSource.exceptions (std::ifstream::failbit | std::ifstream::badbit);
            fragmentShaderSource.exceptions (std::ifstream::failbit | std::ifstream::badbit);
            try
            {
                log.Note("Opening Shader Files...");
                vertexShaderSource.open(vertexShaderPath);
                fragmentShaderSource.open(fragmentShaderPath);
                std::stringstream vShaderStream, fShaderStream;
                vShaderStream << vertexShaderSource.rdbuf();
                fShaderStream << fragmentShaderSource.rdbuf();
                vertexShaderSource.close();
                fragmentShaderSource.close();
                log.Note("Closed Shader Files");
                vertexShaderString = vShaderStream.str();
                fragmentShaderString = fShaderStream.str();
            }
            catch(std::ifstream::failure error)
            {
                log.Error("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
            }
            const char* vertexShaderCode = vertexShaderString.c_str();
            const char* fragmentShaderCode = fragmentShaderString.c_str();
            unsigned int vertexShader, fragmentShader;
            log.Note("Creating Shaders...");
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
            glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
            glCompileShader(vertexShader);
            glCompileShader(fragmentShader);
            int success;
            char infoLog[512];
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                log.Error("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
                log.Error(infoLog);
            }
            else
            {
                log.Note("Created Vertex Shader");
            }
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                log.Error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");
                log.Error(infoLog);
            }
            else
            {
                log.Note("Created Fragment Shader");
            }
            log.Note("Creating Shader Program...");
            shaderProgram = glCreateProgram();
            if(shaderProgram == 0)
            {
                log.Error("Failed To Created Shader Program");
            }
            else
            {
                log.Note("Created Shader Program");
            }
            log.Note("Attaching Vertex Shader...");
            glAttachShader(shaderProgram, vertexShader);
            unsigned int failedShaderNumber = 0;
            int shaderNumber = 0;
            glGetProgramiv(shaderProgram, GL_ATTACHED_SHADERS, &shaderNumber);
            if(shaderNumber < 1)
            {
                log.Error("Failed To Attach Vertex Shader");
                failedShaderNumber++;
            }
            else
            {
                log.Note("Attached Vertex Shader");
            }
            log.Note("Attaching Fragment Shader...");
            glAttachShader(shaderProgram, fragmentShader);
            glGetProgramiv(shaderProgram, GL_ATTACHED_SHADERS, &shaderNumber);
            if(shaderNumber < 2 - failedShaderNumber)
            {
                log.Error("Failed To Attach Fragment Shader");
                failedShaderNumber++;
            }
            else
            {
                log.Note("Attached Fragment Shader");
            }
            glLinkProgram(shaderProgram);
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                log.Error("ERROR::SHADER::PROGRAM::LINKING_FAILED");
                log.Error(infoLog);
            }
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
        }
        void use()
        {
            glUseProgram(shaderProgram);
        }
        void setBool(const std::string &name, bool value) const
        {
            glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
        }
        void setInt(const std::string &name, int value) const
        { 
            glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
        }
        void setFloat(const std::string &name, float value) const
        {
            glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value); 
        } 
};


int main(int argc, char *argv[])
{
    Logger log;
    log.Note("Initializing SDL...");
    int SDLErrorCode = 0;
    SDLErrorCode = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
    if (SDLErrorCode != 0)
    {
        log.FatalError("SDL Failed to Initialize: " + (std::string)SDL_GetError());
        log.FatalError("Exiting With Code " + std::to_string(SDLErrorCode));
        return SDLErrorCode;
    }
    log.Note("Initialized SDL");

    std::string windowTitle = "Ghoul Engine";
    std::string vertexShaderPath = "shaders/vertexShader.glsl";
    std::string fragmentShaderPath = "shaders/fragmentShader.glsl";
    log.Note("Vertex Shader Path: " + vertexShaderPath);
    log.Note("Fragment Shader Path: " + fragmentShaderPath);
    SDL_DisplayMode displayMode;
    log.Note("Obtaining Display Mode...");
    int windowWidth = 600, windowHeight = 400;
    SDLErrorCode = SDL_GetDesktopDisplayMode(0, &displayMode);
    if (SDLErrorCode != 0)
    {
        log.Error("Failed to Obtain Display Mode: \n" + (std::string)SDL_GetError());
        log.Warn("Using Default Resolution");
        log.Note("Window Height: " + std::to_string(windowHeight));
        log.Note("Window Width: " + std::to_string(windowWidth));
    }
    else
    {
        log.Note("Obtained Display Mode");
        windowWidth = displayMode.w / 1.5;
        windowHeight = displayMode.h / 1.5;
        log.Note("Window Height: " + std::to_string(windowHeight));
        log.Note("Window Width: " + std::to_string(windowWidth));
    }

    const char *glsl_version = "#version 460";


    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    log.Note("Creating Window...");
    SDL_Window *window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, windowFlags);
    if(window == NULL)
    {
        log.FatalError("Failed To Create Window: " + (std::string)SDL_GetError());
        log.FatalError("Exiting With Code 1");
        return 1;
    }
    log.Note("Created Window");
    log.Note("Creating OpenGL Context...");
    SDL_GLContext openglContext = SDL_GL_CreateContext(window);
    if(openglContext == NULL)
    {
        log.FatalError("Failed To Create OpenGL Context: " + (std::string)SDL_GetError());
        log.FatalError("Exiting With Code 1");
        return 1;
    }
    log.Note("Created OpenGL Context");
    SDLErrorCode = SDL_GL_MakeCurrent(window, openglContext);
    if (SDLErrorCode != 0)
    {
        log.FatalError("SDL Failed to Setup OpenGL Context: " + (std::string)SDL_GetError());
        log.FatalError("Exiting With Code " + std::to_string(SDLErrorCode));
        return SDLErrorCode;
    }
    log.Note("Setting Up Vsync...");
    if(SDL_GL_SetSwapInterval(1) != 0)
    {
        log.Error("Failed To Setup Vsync");
    }
    else
    {
        log.Note("Setup Vsync");
    }

    log.Note("Initializing GLAD...");
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        log.FatalError("Failed to initialize GLAD");
        log.FatalError("Exiting With Code 1");
        return 1;
    }
    log.Note("Initialized GLAD");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui::StyleColorsDark();
    log.Note("Initializing Imgui For SDL2...");
    if(ImGui_ImplSDL2_InitForOpenGL(window, openglContext) == 0)
    {
        log.FatalError("Failed To Initialize Imgui For SDL2");
        log.FatalError("Exiting With Code 1");
        return 1;
    }
    log.Note("Initialize Imgui For OpenGL");
    log.Note("Initializing Imgui For OpenGL...");
    if(ImGui_ImplOpenGL3_Init(glsl_version) == 0)
    {
        log.FatalError("Failed To Initialize Imgui For OpenGL");
        log.FatalError("Exiting With Code 1");
        return 1;
    }
    log.Note("Initialize Imgui For OpenGL");


    // Setup

    // Vertices
    float vertices[] = {
    // positions          // colors                 // texture coordinates
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // Shader Setup
    Shader shaderProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str(), log);

    // VBO and VAO Setup
    unsigned int VBO, EBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);


    // Variables
    int currentVertexBufferElement = 0;
    float value = 0.0f;
    bool wireframeMode = false;


    bool running = true;
    while (running)
    {
        glClearColor(255, 255, 255 ,255);
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
        ImGui::Begin(windowTitle.c_str());
        ImGui::Text("Current Vertex Buffer Element: ");
        ImGui::SameLine();
        ImGui::SliderInt("###", &currentVertexBufferElement, 0, sizeof(vertices) / sizeof(vertices[0]), "%d", ImGuiSliderFlags_AlwaysClamp);
        ImGui::Text("Vertex Buffer Element Value: ");
        ImGui::SameLine();
        ImGui::SliderFloat("##", &value, -1.0f, 1.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::Checkbox("Wireframe Mode", &wireframeMode);
        ImGui::End();

        // Render
        vertices[currentVertexBufferElement] = value;
        shaderProgram.use();
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO); 
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        if(wireframeMode)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);


        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }
    log.Note("Shutting Down...");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(openglContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    log.Note("Shutdown Success");
    log.Note("Exiting");
    return 0;
}
