#pragma once

#include <string>
#include <vector>
#include <luaCPP.hpp>
#include <GH/lua/luaManager.hpp>

namespace GH::lua {
    bool run(const std::string& code, bool isCore = false);
    bool callFunction(const std::string& function, const std::vector<luaArgument>& arguments = std::vector<luaArgument>(), bool isCore = false);
    bool registerFunction(const std::string& luaAlias, lua_CFunction function, bool isCore = false);

    std::pair<bool, bool> getBoolean(const std::string& name, bool isCore = false);
    std::pair<double, bool> getNumber(const std::string& name, bool isCore = false);
    std::pair<std::string, bool> getString(const std::string& name, bool isCore = false);
}
