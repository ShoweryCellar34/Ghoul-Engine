#pragma once

#include <string>
#include <PNT/Pentagram.hpp>

namespace GH::error {
    enum class codes {
        GAME_FOLDER_NOT_SET,
        GAME_FOLDER_DOES_NOT_EXIST,
        CORE_FILE_ERROR,
        FILE_ERROR,
        CORE_LUA_ERROR,
        LUA_ERROR,
        CORE_PNT_ERROR,
        PNT_ERROR,
        CORE_RESOURCE_ERROR,
        RESOURCE_ERROR,
        CORE_GL_ERROR,
        GL_ERROR
    };

    class exception : std::exception {
    private:
        std::string m_message;

    public:
        exception(const std::string& message);

        const char* what() const throw();
    };

    void triggerError(codes error, const exception& exception = (std::string)"");
    void triggerError(codes error, const PNT::exception& exception);
}
