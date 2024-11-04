#include <GH/lua.hpp>

#include <stdio.h>
#include <string.h>

#include <luaCPP.hpp>

namespace GH {
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
