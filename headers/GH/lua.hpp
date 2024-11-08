#pragma once

#include <string>
#include <luaCPP.hpp>

namespace GH::lua {
    namespace internal {
        class luaState {
        private:
            lua_State* m_L;

        public:
            luaState();
            ~luaState();
            luaState(const luaState&) = delete;
            luaState& operator=(const luaState&) = delete;

            void run(const std::string& code);
            template<typename... types>
            void callFunction(const std::string& function, const types&... arguments);
        };
    }
}
