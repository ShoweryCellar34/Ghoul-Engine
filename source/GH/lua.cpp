#include <GH/lua.hpp>

#include <string.h>
#include <luaCPP.hpp>
#include <GH/error.hpp>

template<typename type>
void handleArgument(lua_State* L, type value) {
    switch(typeid(value).name()) {
        case LUA_TNUMBER:
            handleNumber(L, index);
            break;
        case LUA_TSTRING:
            handleString(L, index);
            break;
        case LUA_TBOOLEAN:
            handleBoolean(L, index);
            break;
        default:
            std::cout << "Unknown type" << std::endl;
            break;
    }
}

namespace GH::lua {
    namespace internal {
        // LuaState definitions

        luaState::luaState() : m_L(luaL_newstate()) {
            luaL_openlibs(m_L);
        }

        luaState::~luaState() {
            lua_close(m_L);
        }

        void luaState::run(const std::string& code) {
            int loadResult = luaL_loadstring(m_L, code.c_str());
            if(loadResult != LUA_OK) {
                throw std::runtime_error(lua_tostring(m_L, -1));
            }
            int runResult = lua_pcall(m_L, 0, LUA_MULTRET, 0);
            if(runResult != LUA_OK) {
                throw std::runtime_error(lua_tostring(m_L, -1));
            }
        }

        template<typename... types>
        void luaState::callFunction(const std::string& function, const types&... arguments) {
            lua_getglobal(m_L, function.c_str());
            if(lua_type(m_L, -1) != LUA_TFUNCTION) {
                throw std::runtime_error("Function does not exist or is not of type function.");
            }
            (handleArgument(m_L, arguments), ...);
        }
    }
}
