#include <GH/lua/scripting.hpp>

#include <GH/cpp/globalsAndDefines.hpp>

namespace GH::lua {
    bool run(const std::string& code, bool isCore) {
        try {
            internal::g_luaState.run(code);
            if(isCore) {
                ::userLogger.get()->info("Loaded non-core lua code successfully");
            } else {
                ::userLogger.get()->info("Loaded core lua code successfully");
            }
            return true;
        } catch(const error::exception& error) {
            if(isCore) {
                triggerError(GH::error::codes::CORE_LUA_ERROR, error);
            } else {
                triggerError(GH::error::codes::LUA_ERROR, error);
            }
            return false;
        }
    }

    bool callFunction(const std::string& function, const std::vector<luaArgument>& arguments, bool isCore) {
        try {
            internal::g_luaState.callFunction(function, arguments);
            if(isCore) {
                ::userLogger.get()->trace("Called lua function with core criticality successfully");
            } else {
                ::userLogger.get()->trace("Called lua function with non-core criticality successfully");
            }
            return true;
        } catch(const error::exception& error) {
            if(isCore) {
                triggerError(GH::error::codes::CORE_LUA_ERROR, error);
            } else {
                triggerError(GH::error::codes::LUA_ERROR, error);
            }
            return false;
        }
    }

    bool registerFunction(const std::string& luaAlias, lua_CFunction function, bool isCore) {
        try {
            internal::g_luaState.registerFunction(luaAlias, function);
            if(isCore) {
                ::userLogger.get()->info("Registered non-core lua function successfully");
            } else {
                ::userLogger.get()->info("Registered core lua function successfully");
            }
            return true;
        } catch(const error::exception& error) {
            if(isCore) {
                triggerError(GH::error::codes::CORE_LUA_ERROR, error);
            } else {
                triggerError(GH::error::codes::LUA_ERROR, error);
            }
            return false;
        }
    }

    std::pair<bool, bool> getBoolean(const std::string& name, bool isCore) {
        try {
            bool result = internal::g_luaState.getBoolean(name);
            if(isCore) {
                ::userLogger.get()->trace("Queried value of boolean \"" + name + "\" with core criticality");
            } else {
                ::userLogger.get()->trace("Queried value of boolean \"" + name + "\" with non-core criticality");
            }
            return {result, true};
        } catch(const error::exception& error) {
            if(isCore) {
                triggerError(GH::error::codes::CORE_LUA_ERROR, error);
            } else {
                triggerError(GH::error::codes::LUA_ERROR, error);
            }
            return {false, false};
        }
    }

    std::pair<double, bool> getNumber(const std::string& name, bool isCore) {
        try {
            double result = internal::g_luaState.getNumber(name);
            if(isCore) {
                ::userLogger.get()->trace("Queried value of number \"" + name + "\" with core criticality");
            } else {
                ::userLogger.get()->trace("Queried value of number \"" + name + "\" with non-core criticality");
            }
            return {result, true};
        } catch(const error::exception& error) {
            if(isCore) {
                triggerError(GH::error::codes::CORE_LUA_ERROR, error);
            } else {
                triggerError(GH::error::codes::LUA_ERROR, error);
            }
            return {0, false};
        }
    }

    std::pair<std::string, bool> getString(const std::string& name, bool isCore) {
        try {
            std::string result = internal::g_luaState.getString(name);
            if(isCore) {
                ::userLogger.get()->trace("Queried value of string \"" + name + "\" with core criticality");
            } else {
                ::userLogger.get()->trace("Queried value of string \"" + name + "\" with non-core criticality");
            }
            return {result, true};
        } catch(const error::exception& error) {
            if(isCore) {
                triggerError(GH::error::codes::CORE_LUA_ERROR, error);
            } else {
                triggerError(GH::error::codes::LUA_ERROR, error);
            }
            return {"", false};
        }
    }
}
