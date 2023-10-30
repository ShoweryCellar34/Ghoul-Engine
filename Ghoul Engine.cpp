#include "include/Ghoul Engine/Ghoul Engine.hpp"

int main(int argc, char *argv[])
{
    // Setup
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
    std::string texturePath = "assets/ghoul.png";
    log.Note("Vertex Shader Path: " + vertexShaderPath);
    log.Note("Fragment Shader Path: " + fragmentShaderPath);
    log.Note("Texture Path: " + texturePath);
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
    if (window == NULL)
    {
        log.FatalError("Failed To Create Window: " + (std::string)SDL_GetError());
        log.FatalError("Exiting With Code 1");
        return 1;
    }
    log.Note("Created Window");
    log.Note("Creating OpenGL Context...");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GLContext openglContext = SDL_GL_CreateContext(window);
    if (openglContext == NULL)
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
    if (SDL_GL_SetSwapInterval(1) != 0)
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
    if (ImGui_ImplSDL2_InitForOpenGL(window, openglContext) == 0)
    {
        log.FatalError("Failed To Initialize Imgui For SDL2");
        log.FatalError("Exiting With Code 1");
        return 1;
    }
    log.Note("Initialize Imgui For OpenGL");
    log.Note("Initializing Imgui For OpenGL...");
    if (ImGui_ImplOpenGL3_Init(glsl_version) == 0)
    {
        log.FatalError("Failed To Initialize Imgui For OpenGL");
        log.FatalError("Exiting With Code 1");
        return 1;
    }
    log.Note("Initialize Imgui For OpenGL");

    // OpenGL Setup

    // Vertices
    float vertices[] = {
        // positions      // colors               // texture coordinates
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f   // top left
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // Shader Setup
    Shader shaderProgram(vertexShaderPath, fragmentShaderPath, texturePath, log);

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    // Variables
    int currentVertexBufferElement = 0;
    float value = 0.0f;
    bool wireframeMode = false;
    bool useTexture = false;

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
        ImGui::Begin(windowTitle.c_str());
        ImGui::Text("Current Vertex Buffer Element: ");
        ImGui::SameLine();
        ImGui::SliderInt("##SliderInt1", &currentVertexBufferElement, 0, sizeof(vertices) / sizeof(vertices[0]), "%d", ImGuiSliderFlags_AlwaysClamp);
        ImGui::Text("Vertex Buffer Element Value: ");
        ImGui::SameLine();
        ImGui::SliderFloat("##SliderFloat1", &value, -1.0f, 1.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::Checkbox("Wireframe Mode", &wireframeMode);
        if (ImGui::Button("Toggle Texture On/Off"))
        {
            useTexture = !useTexture;
            shaderProgram.setBool("useTexture", useTexture);
        }
        ImGui::Text("Texture Path: ");
        ImGui::SameLine();
        ImGui::InputText("##InputText1", &texturePath);
        if (ImGui::Button("Update Image"))
        {
            shaderProgram.updateTexture(texturePath);
        }
        ImGui::End();

        // Render
        vertices[currentVertexBufferElement] = value;
        shaderProgram.use();
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        if (wireframeMode)
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
