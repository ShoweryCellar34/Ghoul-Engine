#include <Pentagram.hpp>

PNT::image image;

void eventCallback(PNT::Window* window, PNT::windowEvent event) {
    if(event.eventType == PNT_EVENT_TYPE_DROP) {
        image.load(event.dropEvent.paths[0]);
        window->setDimentions(image.getDimentions().first, image.getDimentions().second);
        image.loadOnGPU();
    }
}

int main(int argc, char *argv[]) {
    if(!PNT::init()) {
        return 1;
    }

    image.load("res\\textures\\logo\\ghoul.png");
    PNT::Window window("Drag'n Drop", image.getDimentions().first, image.getDimentions().second, 500, 500, ImGuiConfigFlags_ViewportsEnable | ImGuiConfigFlags_DockingEnable);
    image.loadOnGPU();
    window.setEventCallback(eventCallback);

    
    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex shader.
    PNT::file vertexFile("res\\shaders\\vertex.glsl");
    PNT::shader vertexShader(vertexFile.getContents(), GL_VERTEX_SHADER);
    vertexShader.compile();

    // Fragment shader.
    PNT::file fragmentFile("res\\shaders\\fragment.glsl");
    PNT::shader fragmentShader(fragmentFile.getContents(), GL_FRAGMENT_SHADER);
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



        window.endFrame();
    }

    PNT::deinit();
    return 0;
}
