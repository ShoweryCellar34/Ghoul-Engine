#ifndef CPP_GAME
#include <GH/lua/luaMain.hpp>

int main(int argc, char* argv[]) {
    return luaMain(argc, argv);
}
#endif
#ifdef CPP_GAME
#include <GH/cpp/cppMain.hpp>

int main(int argc, char* argv[]) {
    return cppMain(argc, argv);
}
#endif
