#include <GH/cpp/error.hpp>

#include <PNT/Pentagram.hpp>
#include <GH/cpp/globalsAndDefines.hpp>

namespace GH::error {
    exception::exception(const std::string& message) : m_message(message) {
    }

    const char* exception::what() const throw() {
        return m_message.c_str();
    }

    void triggerError(codes error, const exception& exception) {
        switch(error) {
            case codes::GAME_FOLDER_DOES_NOT_EXIST:
                ::userLogger.get()->error("Game folder \"{}\" does not exist, exiting with code {}", g_gameFolder, (int)error);
                exit((int)error);
                break;
            case codes::GAME_FOLDER_NOT_SET:
                ::userLogger.get()->error("Game folder not set, exiting with code {}", (int)error);
                exit((int)error);
                break;
            case codes::CORE_RESOURCE_ERROR:
                ::userLogger.get()->error("Core resource operation failed with error message \"{}\", exiting with code {}", exception.what(), (int)error);
                exit((int)error);
                break;
            case codes::RESOURCE_ERROR:
                ::userLogger.get()->warn("Resource operation failed with error message \"{}\"", exception.what());
                break;
            case codes::CORE_LUA_ERROR:
                ::userLogger.get()->error("Core lua code errored with message \"{}\", exiting with code {}", exception.what(), (int)error);
                exit((int)error);
                break;
            case codes::LUA_ERROR:
                ::userLogger.get()->warn("Lua code errored with message \"{}\"", exception.what());
                break;
        }
    }

    void triggerError(codes error, const PNT::exception& exception) {
        switch(error) {
            case codes::CORE_PNT_ERROR:
                ::userLogger.get()->error("Pentagram with core criticality errored with message \"{}\", and code {}, exiting with code {}", exception.what(), (int)exception.whatErrorCode(), (int)error);
                exit((int)error);
                break;
            case codes::PNT_ERROR:
                ::userLogger.get()->warn("Pentagram with non-core criticality errored with message \"{}\", and code {}", exception.what(), (int)exception.whatErrorCode());
                break;
        }
    }
}
