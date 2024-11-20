#pragma once

#include <string>
#include <vector>
#include <luaCPP.hpp>
#include <GH/lua/luaManager.hpp>

namespace GH::lua {
    bool run(const std::string& code, bool isCore = false);
    bool callFunction(const std::string& function, const std::vector<luaArgument>& arguments, bool isCore);
    bool registerFunction(const std::string& luaAlias, lua_CFunction function, bool isCore);

    std::pair<bool, bool> getBoolean(const std::string& name, bool isCore);
    std::pair<double, bool> getNumber(const std::string& name, bool isCore);
    std::pair<std::string, bool> getString(const std::string& name, bool isCore);
}
