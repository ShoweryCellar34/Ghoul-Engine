#ifndef CPP_GAME
#include <GH/lua/luaMain.hpp>

int main(int argc, char* argv[]) {
    userLogger.get()->info("Launching in LUA mode");
    return luaMain(argc, argv);
}
#endif
#ifdef CPP_GAME
#include <GH/cpp/cppMain.hpp>

int main(int argc, char* argv[]) {
    userLogger.get()->info("Launching in CPP mode");
    return cppMain(argc, argv);
}
#endif
