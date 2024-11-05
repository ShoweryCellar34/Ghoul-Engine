#pragma once

#include <string>
#include <luaCPP.hpp>

namespace GH {
    class script {
    private:
        lua_State* m_L;
        std::string m_code;

    public:
        script(const std::string& code, bool runNow = false);
        ~script();
        script(const script&) = delete;
        script& operator=(const script&) = delete;
    };
}
