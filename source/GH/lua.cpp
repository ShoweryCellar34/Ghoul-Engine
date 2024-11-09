#include <GH/lua.hpp>

#include <PNT/Pentagram.hpp>
#include <luaCPP.hpp>

template<typename type>
void handleArgument(lua_State* L, type value) {
    ::userLogger.get()->info(typeid(value).name());
    // switch(typeid(value).name()) {
    //     case LUA_TNUMBER:
    //         handleNumber(L, index);
    //         break;
    //     case LUA_TSTRING:
    //         handleString(L, index);
    //         break;
    //     case LUA_TBOOLEAN:
    //         handleBoolean(L, index);
    //         break;
    //     default:
    //         std::cout << "Unknown type" << std::endl;
    //         break;
    // }
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
                throw error::exception(lua_tostring(m_L, -1));
            }
            int runResult = lua_pcall(m_L, 0, LUA_MULTRET, 0);
            if(runResult != LUA_OK) {
                throw error::exception(lua_tostring(m_L, -1));
            }
        }
    }
}
