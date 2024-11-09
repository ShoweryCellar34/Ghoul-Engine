#pragma once

#include <string>

namespace GH::error {
    enum class codes {
        GAME_FOLDER_NOT_SET,
        GAME_FOLDER_DOES_NOT_EXIST,
        CORE_RESOURCE_ERROR,
        RESOURCE_ERROR,
        CORE_LUA_ERROR,
        LUA_ERROR
    };

    class exception : std::exception {
    private:
        std::string m_message;

    public:
        exception(const std::string& message);

        const char* what() const throw();
    };

    void triggerError(codes error, const exception& exception = exception(""));
}
