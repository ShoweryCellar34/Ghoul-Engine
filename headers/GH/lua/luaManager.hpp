#pragma once

#include <PNT/Pentagram.hpp>
#include <luaCPP.hpp>
#include <GH/cpp/error.hpp>

namespace GH::lua {
    enum class argumentType {
        NONE,
        BOOLEAN,
        NUMBER,
        STRING
    };

    struct luaArgument {
        double m_boolean;
        double m_number;
        std::string m_string;
        argumentType m_type;

        luaArgument(bool boolean, double number, const std::string& string, argumentType type);
    };

    luaArgument booleanArgument(bool boolean);
    luaArgument numberArgument(double number);
    luaArgument stringArgument(const std::string& string);

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
            void callFunction(const std::string& function, const std::vector<luaArgument>& arguments = std::vector<luaArgument>());
            void registerFunction(const std::string& luaAlias, lua_CFunction function);

            bool getBoolean(const std::string& name) const;
            double getNumber(const std::string& name) const;
            std::string getString(const std::string& name) const;
        };
    }
}
