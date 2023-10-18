#include "include/GLAD/glad.h"
#include "include/IMGUI/imgui.h"
#include "include/IMGUI/imgui_stdlib.h"
#include "include/IMGUI/imgui_impl_sdl2.h"
#include "include/IMGUI/imgui_impl_opengl3.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "include/SDL2/SDL.h"


class Log
{
    private:
    std::string tempBuffer;
    std::string saveBuffer;
    int flushThreshold = 300;
    bool useSaveBuffer = false;
        void log(std::string prefix, std::string message)
        {
            tempBuffer = prefix;
            tempBuffer.append(message);
            tempBuffer.append("\n");
            if(print)
            {
                std::cout << tempBuffer;
            }
            if(save)
            {
                if(useSaveBuffer)
                {
                    saveBuffer.append(tempBuffer);
                }
                if(saveBuffer.length() > flushThreshold)
                {
                    
                }
            }
        }
    public:
        bool print = true;
        bool save = true;
        void Note(std::string message)
        {
            log("NOTE: ", message);
        }
        void Warn(std::string message)
        {
            log("WARN: ", message);
        }
        void Error(std::string message)
        {
            log("ERROR: ", message);
        }
};


class Shader
{
    public:
        unsigned int shaderProgram;
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
        {
            std::string vertexShaderString;
            std::string fragmentShaderString;
            std::ifstream vertexShaderSource;
            std::ifstream fragmentShaderSource;
            vertexShaderSource.exceptions (std::ifstream::failbit | std::ifstream::badbit);
            fragmentShaderSource.exceptions (std::ifstream::failbit | std::ifstream::badbit);
            try
            {
                vertexShaderSource.open(vertexShaderPath);
                fragmentShaderSource.open(fragmentShaderPath);
                std::stringstream vShaderStream, fShaderStream;
                vShaderStream << vertexShaderSource.rdbuf();
                fShaderStream << fragmentShaderSource.rdbuf();
                vertexShaderSource.close();
                fragmentShaderSource.close();
                vertexShaderString   = vShaderStream.str();
                fragmentShaderString = fShaderStream.str();
            }
            catch(std::ifstream::failure error)
            {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            }
            const char* vertexShaderCode = vertexShaderString.c_str();
            const char* fragmentShaderCode = fragmentShaderString.c_str();
            unsigned int vertexShader, fragmentShader;
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
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            };
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            };
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
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
    std::cout << "Initializing SDL..." << std::endl;
    int SDLErrorCode = 0;
    SDLErrorCode = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
    if (SDLErrorCode != 0)
    {
        std::cout << "SDL Failed to Initialize: \n" << SDL_GetError() << std::endl;
        std::cout << "Exiting With Code: " << SDLErrorCode << std::endl;
        return SDLErrorCode;
    }
    std::cout << "Initialized SDL" << std::endl;

    std::string windowTitle = "Ghoul Engine";
    std::string vertexShaderPath = "shaders/vertexShader.glsl";
    std::string fragmentShaderPath = "shaders/fragmentShader.glsl";
    std::cout << "Vertex Shader Path: " << vertexShaderPath << std::endl;
    std::cout << "Fragment Shader Path: " << fragmentShaderPath << std::endl;
    SDL_DisplayMode displayMode;
    std::cout << "Obtaining Display Mode..." << std::endl;
    SDLErrorCode = SDL_GetDesktopDisplayMode(0, &displayMode);
    if (SDLErrorCode != 0)
    {
        std::cout << "Failed to Obtain Display Mode: \n" << SDL_GetError() << std::endl;
        std::cout << "Exiting With Code: " << SDLErrorCode << std::endl;
        return SDLErrorCode;
    }
    std::cout << "Obtained Display Mode" << std::endl;
    int windowWidth = displayMode.w / 1.5;
    int windowHeight = displayMode.h / 1.5;
    std::cout << "Window Height: " << windowHeight << std::endl;
    std::cout << "Window Width: " << windowWidth << std::endl;

    const char *glsl_version = "#version 460";

    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window *window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, windowFlags);
    SDL_GLContext openglContext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, openglContext);
    SDL_GL_SetSwapInterval(1);

    std::cout << "Initializing GLAD..." << std::endl;
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cout << "Initialized GLAD" << std::endl;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(window, openglContext);
    ImGui_ImplOpenGL3_Init(glsl_version);


    // Setup

    // Shaders

    // Vertices
    float vertices[] = {
        0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,
        4, 5, 6
    };

    // Shader Setup
    Shader shaderProgram(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

    // VBO and VAO Setup

    unsigned int VBO, EBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
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
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(openglContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
