#include <GH/lua.hpp>

#include <stdio.h>
#include <string.h>

#include <luaCPP.hpp>

static int pintapoop(lua_State *L) {
    printf("WWWWAAAAAAAAAA");
    return 0;
}

namespace GH {
    // Script definitions

    GH::script::script(const std::string& code, bool runNow) : m_code(code) {
        if(runNow) {
            m_L = luaL_newstate();
            luaL_openlibs(m_L);
            lua_pushcfunction(m_L, pintapoop);
            lua_setglobal(m_L, "pintapoop");
            luaL_dostring(m_L, m_code.c_str());
        }
    }

    script::~script() {
    }

    void lua() {
        char buff[256];
        int error;
        lua_State* L = luaL_newstate();
        
        luaL_dostring(L, "x = 69420");
        lua_getglobal(L, "x");
        lua_Number number = lua_tonumber(L, 1);
        printf("x = %d\n", (int)number);
        
        lua_close(L);
    }
}
