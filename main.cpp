#include <Pentagram.hpp>

void eventCallback(PNT::Window* window, PNT::windowEvent event) {
}

int main(int argc, char *argv[]) {
    if(!PNT::init()) {
        return 1;
    }

    PNT::Window window("Drag'n Drop");
    window.setEventCallback(eventCallback);
    PNT::file imageFile("res\\textures\\logo\\ghoul.png");
    PNT::image image(imageFile)

}
