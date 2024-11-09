#pragma once

#include <PNT/Pentagram.hpp>
#include <luaCPP.hpp>
#include <GH/error.hpp>

namespace GH::lua {
    namespace internal {
        struct luaArgument {
            double m_boolean;
            double m_number;
            std::string m_string;
            std::string m_type;

            luaArgument() : m_boolean(0), m_number(0), m_string(0), m_type("") {
            }
        };

        class luaState {
        private:
            lua_State* m_L;
            template<typename type, typename... types>
            std::vector<luaArgument> callFunction(void*, type nextArgument, const types&... arguments)  {
                luaArgument argument;
                if(std::is_same<type, bool>::value) {
                    argument.m_type = "boolean";
                    argument.m_boolean = *reinterpret_cast<bool*>(&nextArgument);
                } else if(std::is_same<type, double>::value) {
                    argument.m_type = "number";
                    argument.m_number = *reinterpret_cast<double*>(&nextArgument);
                } else if(std::is_same<type, std::string>::value) {
                    argument.m_type = "string";
                    argument.m_string = *reinterpret_cast<std::string*>(&nextArgument);
                }
                ::userLogger.get()->info("{}", typeid(nextArgument).name());

                std::vector<luaArgument> argumentList = {argument};
                if(sizeof...(arguments) < 1) {
                    return argumentList;
                }
                std::vector<luaArgument> argumentList2 = callFunction(nullptr, arguments...);
                argumentList2.push_back(argument);
                return argumentList2;
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
                    throw error::exception("Function \"" + function + "\" does not exist or is not of type function.");
                }

                std::vector<luaArgument> argumentList = callFunction(nullptr, arguments...);

                if(lua_pcall(m_L, 0, 0, 0) != LUA_OK) {
                    throw error::exception("Failed to call function \"" + function + "\" with error \"" + lua_tostring(m_L, -1) + "\".");
                }
            }
        };
    }
}
