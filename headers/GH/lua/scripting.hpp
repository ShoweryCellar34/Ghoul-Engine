#pragma once

#include <string>
#include <vector>
#include <luaCPP.hpp>
#include <GH/lua/luaManager.hpp>

namespace GH::lua {
    bool run(const std::string& code, bool isCore = false);
    bool callFunction(const std::string& function, const std::vector<luaArgument>& arguments = std::vector<luaArgument>(), bool isCore = false);
    bool registerFunction(const std::string& luaAlias, lua_CFunction function, bool isCore = false);
}
