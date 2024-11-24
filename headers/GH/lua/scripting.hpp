#pragma once

#include <string>
#include <vector>
#include <luaCPP.hpp>
#include <GH/lua/luaManager.hpp>

namespace GH::lua {
    bool wasSuccessful();

    void run(const std::string& code, bool isCore = false);
    void callFunction(const std::string& function, const std::vector<luaArgument>& arguments, bool isCore);
    void registerFunction(const std::string& luaAlias, lua_CFunction function, bool isCore);

    bool getBoolean(const std::string& name, bool isCore);
    double getNumber(const std::string& name, bool isCore);
    std::string getString(const std::string& name, bool isCore);

    void loadSettings();
}
