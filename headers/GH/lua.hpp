#pragma once

#include <PNT/Pentagram.hpp>
#include <luaCPP.hpp>
#include <GH/error.hpp>

namespace GH::lua {
    namespace internal {
        class luaState {
        private:
            lua_State* m_L;
            template<typename type, typename... types>
            void callFunction(void*, type nextArgument, const types&... arguments)  {
                ::userLogger.get()->info("{}", nextArgument);

                if(sizeof...(arguments) < 1) {
                    return;
                }
                callFunction(nullptr, arguments...);
            }

        public:
            luaState();
            ~luaState();
            luaState(const luaState&) = delete;
            luaState& operator=(const luaState&) = delete;

            void run(const std::string& code);
            template<typename... types>
            void callFunction(const std::string& function, const types&... arguments)  {
                lua_getglobal(m_L, function.c_str());
                if(lua_type(m_L, -1) != LUA_TFUNCTION) {
                    throw error::exception("Function does not exist or is not of type function.");
                }
                callFunction(nullptr, arguments...);
            }
        };
    }
}
