#include <GH/lua/luaManager.hpp>

#include <PNT/Pentagram.hpp>
#include <luaCPP.hpp>

namespace GH::lua {
    luaArgument::luaArgument(bool boolean, double number, const std::string& string, argumentType type) : m_boolean(boolean), m_number(number), m_string(string), m_type(type) {
    }

    luaArgument booleanArgument(bool boolean) {
        return luaArgument(boolean, 0, "", argumentType::BOOLEAN);
    }

    luaArgument numberArgument(double number) {
        return luaArgument(0, number, "", argumentType::NUMBER);
    }

    luaArgument stringArgument(const std::string& string) {
        return luaArgument(0, 0, string, argumentType::STRING);
    }

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

        void luaState::callFunction(const std::string& function, const std::vector<luaArgument>& arguments) {
            lua_getglobal(m_L, function.c_str());
            if(lua_type(m_L, -1) != LUA_TFUNCTION) {
                throw error::exception("Function \"" + function + "\" does not exist or is not of type function.");
            }

            for(const luaArgument& argument : arguments) {
                switch(argument.m_type) {
                    case argumentType::BOOLEAN:
                        lua_pushboolean(m_L, argument.m_boolean);
                        break;
                    case argumentType::NUMBER:
                        lua_pushnumber(m_L, argument.m_number);
                        break;
                    case argumentType::STRING:
                        lua_pushstring(m_L, argument.m_string.c_str());
                        break;
                }
            }

            if(lua_pcall(m_L, arguments.size(), 0, 0) != LUA_OK) {
                throw error::exception("Failed to call function \"" + function + "\" with error \"" + lua_tostring(m_L, -1) + "\".");
            }
        }

        void luaState::registerFunction(const std::string& luaAlias, lua_CFunction function) {
            lua_getglobal(m_L, luaAlias.c_str());
            if(lua_type(m_L, -1) != LUA_TNIL) {
                throw error::exception("Alias \"" + luaAlias + "\" alread in use.");
            }

            lua_pushcfunction(m_L, function);
            lua_setglobal(m_L, luaAlias.c_str());
        }
    }
}
