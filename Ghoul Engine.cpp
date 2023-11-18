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
        log.FatalError("SDL Failed to Initialize: \n" + (std::string)SDL_GetError());
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
        log.Note("Window Width: " + std::to_string(windowWidth));
        log.Note("Window Height: " + std::to_string(windowHeight));
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
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    // Variables
    bool wireframeMode = false;
    bool useTexture = true;
    std::string stringItems[IM_ARRAYSIZE(vertices) / 9];
    int currentOption = 0;
    for (int i = 0; i < IM_ARRAYSIZE(vertices) / 9; i++)
    {
        stringItems[i] = "Vertex " + std::to_string(i + 1);
    }
    const char *items[IM_ARRAYSIZE(vertices) / 9];
    for (int i = 0; i < IM_ARRAYSIZE(vertices) / 9; i++)
    {
        items[i] = stringItems[i].c_str();
    }
    float vertexPosition[] = {vertices[0], vertices[1], vertices[2]};
    float vertexColor[] = {vertices[3], vertices[4], vertices[5], vertices[6]};
    float vertexTextureCoordinates[] = {vertices[7], vertices[8]};

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
        ImGui::Text("Current Vertex: ");
        ImGui::SameLine();
        if (ImGui::BeginCombo("##Combo1", items[currentOption]))
        {
            for (int i = 0; i < IM_ARRAYSIZE(items); i++)
            {
                bool is_selected = (currentOption == i);
                if (ImGui::Selectable(items[i], is_selected))
                {
                    currentOption = i;
                    vertexPosition[0] = vertices[(currentOption * 9)];
                    vertexPosition[1] = vertices[(currentOption * 9) + 1];
                    vertexPosition[2] = vertices[(currentOption * 9) + 2];
                    vertexColor[0] = vertices[(currentOption * 9) + 3];
                    vertexColor[1] = vertices[(currentOption * 9) + 4];
                    vertexColor[2] = vertices[(currentOption * 9) + 5];
                    vertexColor[3] = vertices[(currentOption * 9) + 6];
                    vertexTextureCoordinates[0] = vertices[(currentOption * 9) + 7];
                    vertexTextureCoordinates[1] = vertices[(currentOption * 9) + 8];
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        ImGui::Text((stringItems[currentOption] + " Position").c_str());
        ImGui::SameLine();
        ImGui::SliderFloat3("##SliderFloat31", vertexPosition, -1.0f, 1.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::Text((stringItems[currentOption] + " Color").c_str());
        ImGui::SameLine();
        ImGui::SliderFloat4("##SliderFloat41", vertexColor, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::Text((stringItems[currentOption] + " Texture Coordinates").c_str());
        ImGui::SameLine();
        ImGui::SliderFloat2("##SliderFloat21", vertexTextureCoordinates, 0.0f, 1.0f, "%.3f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::Text("Texture Path: ");
        ImGui::SameLine();
        ImGui::InputText("##InputText1", &texturePath);
        if (ImGui::IsItemDeactivatedAfterEdit())
        {
            shaderProgram.updateTexture(texturePath);
        }
        if (ImGui::Button((useTexture ? "Turn Off Texture" : "Turn On Texture")))
        {
            useTexture = !useTexture;
        }
        ImGui::Text("Wireframe Mode");
        ImGui::SameLine();
        ImGui::Checkbox("##CheckBox1", &wireframeMode);
        ImGui::End();

        // Render
        shaderProgram.setBool("useTexture", useTexture);
        shaderProgram.use();
        vertices[(currentOption * 9)] = vertexPosition[0];
        vertices[(currentOption * 9) + 1] = vertexPosition[1];
        vertices[(currentOption * 9) + 2] = vertexPosition[2];
        vertices[(currentOption * 9) + 3] = vertexColor[0];
        vertices[(currentOption * 9) + 4] = vertexColor[1];
        vertices[(currentOption * 9) + 5] = vertexColor[2];
        vertices[(currentOption * 9) + 6] = vertexColor[3];
        vertices[(currentOption * 9) + 7] = vertexTextureCoordinates[0];
        vertices[(currentOption * 9) + 8] = vertexTextureCoordinates[1];
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
