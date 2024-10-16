#pragma once

#include <cstddef>
#include <string>
#include <glad/gl.h>

namespace GH {
    class texture {
    private:
        GladGLContext* m_GL;
        size_t m_ID, m_width, m_height;
        unsigned char* m_data;

    public:
        texture();
        texture(GladGLContext* GL, unsigned char* data, size_t width, size_t height);
        ~texture();

        texture(const texture&) = delete;
        texture& operator=(const texture&) = delete;

        void load();
        void unload();
        void setData(const std::string& data);
        void setGL(GladGLContext* GL);

        const unsigned char* getData();
        size_t getID();
        const GladGLContext* getGL();
    };
}
