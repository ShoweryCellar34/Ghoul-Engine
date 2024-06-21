#include <Pentagram.hpp>

void eventCallback(PNT::Window *window, PNT::windowEvent event) {
}

int main(int argc, char *argv[]) {
    if(!PNT::init()) {
        return 1;
    }

    PNT::Window window("Ghoul Engine", 1000, 700, 200, 200, ImGuiConfigFlags_ViewportsEnable | ImGuiConfigFlags_DockingEnable);
    window.setEventCallback(&eventCallback);
    window.setClearColor(0.25f, 0.25f, 0.25f, 0.25f);

    // Set icon.
    PNT::image icon("res\\textures\\logo\\ghoul32x32.png");
    window.setIcon(icon);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex shader.
    PNT::shader vertexShader(PNT::fileToString("res\\shaders\\vertex.glsl").c_str(), GL_VERTEX_SHADER);
    vertexShader.compile();

    // Fragment shader.
    PNT::shader fragmentShader(PNT::fileToString("res\\shaders\\fragment.glsl").c_str(), GL_FRAGMENT_SHADER);
    fragmentShader.compile();

    // Shader program.
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader.getID());
    glAttachShader(shaderProgram, fragmentShader.getID());
    glLinkProgram(shaderProgram);

    while(!window.shouldClose()) {
        PNT::processEvents();

        window.startFrame();
        ImGui::Begin("Controls");
        ImGui::End();

        window.endFrame();
    }

    PNT::deinit();
    return 0;
}
