#include <GH/lua/scripting.hpp>

#include <GH/cpp/globalsAndDefines.hpp>

namespace GH::lua {
    bool success = false;

    bool wasSuccessful() {
        return success;
    }

    void run(const std::string& code, bool isCore) {
        try {
            internal::g_luaState.run(code);
            if(isCore) {
                ::userLogger.get()->info("Loaded non-core lua code successfully");
            } else {
                ::userLogger.get()->info("Loaded core lua code successfully");
            }
            success = true;
        } catch(const error::exception& error) {
            if(isCore) {
                triggerError(GH::error::codes::CORE_LUA_ERROR, error);
            } else {
                triggerError(GH::error::codes::LUA_ERROR, error);
            }
            success = false;
        }
    }

    void callFunction(const std::string& function, const std::vector<luaArgument>& arguments, bool isCore) {
        try {
            internal::g_luaState.callFunction(function, arguments);
            if(isCore) {
                ::userLogger.get()->trace("Called lua function with core criticality successfully");
            } else {
                ::userLogger.get()->trace("Called lua function with non-core criticality successfully");
            }
            success = true;
        } catch(const error::exception& error) {
            if(isCore) {
                triggerError(GH::error::codes::CORE_LUA_ERROR, error);
            } else {
                triggerError(GH::error::codes::LUA_ERROR, error);
            }
            success = false;
        }
    }

    void registerFunction(const std::string& luaAlias, lua_CFunction function, bool isCore) {
        try {
            internal::g_luaState.registerFunction(luaAlias, function);
            if(isCore) {
                ::userLogger.get()->info("Registered non-core lua function successfully");
            } else {
                ::userLogger.get()->info("Registered core lua function successfully");
            }
            success = true;
        } catch(const error::exception& error) {
            if(isCore) {
                triggerError(GH::error::codes::CORE_LUA_ERROR, error);
            } else {
                triggerError(GH::error::codes::LUA_ERROR, error);
            }
            success = false;
        }
    }

    bool getBoolean(const std::string& name, bool isCore) {
        try {
            bool result = internal::g_luaState.getBoolean(name);
            if(isCore) {
                ::userLogger.get()->trace("Queried value of boolean \"" + name + "\" with core criticality");
            } else {
                ::userLogger.get()->trace("Queried value of boolean \"" + name + "\" with non-core criticality");
            }
            success = true;
            return result;
        } catch(const error::exception& error) {
            if(isCore) {
                triggerError(GH::error::codes::CORE_LUA_ERROR, error);
            } else {
                triggerError(GH::error::codes::LUA_ERROR, error);
            }
            return false;
        }
    }

    double getNumber(const std::string& name, bool isCore) {
        try {
            double result = internal::g_luaState.getNumber(name);
            if(isCore) {
                ::userLogger.get()->trace("Queried value of number \"" + name + "\" with core criticality");
            } else {
                ::userLogger.get()->trace("Queried value of number \"" + name + "\" with non-core criticality");
            }
            success = true;
            return result;
        } catch(const error::exception& error) {
            if(isCore) {
                triggerError(GH::error::codes::CORE_LUA_ERROR, error);
            } else {
                triggerError(GH::error::codes::LUA_ERROR, error);
            }
            success = false;
            return 0;
        }
    }

    std::string getString(const std::string& name, bool isCore) {
        try {
            std::string result = internal::g_luaState.getString(name);
            if(isCore) {
                ::userLogger.get()->trace("Queried value of string \"" + name + "\" with core criticality");
            } else {
                ::userLogger.get()->trace("Queried value of string \"" + name + "\" with non-core criticality");
            }
            success = true;
            return result;
        } catch(const error::exception& error) {
            if(isCore) {
                triggerError(GH::error::codes::CORE_LUA_ERROR, error);
            } else {
                triggerError(GH::error::codes::LUA_ERROR, error);
            }
            success = false;
            return "";
        }
    }
}
