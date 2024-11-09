#pragma once

#include <string>
#include <glad/gl.h>

namespace GH {
    class texture {
    private:
        GladGLContext* m_GL;
        unsigned int m_ID, m_width, m_height, m_channels;
        unsigned char* m_data;

    public:
        texture();
        texture(GladGLContext* GL, const std::string& data);
        ~texture();

        texture(const texture&) = delete;
        texture& operator=(const texture&) = delete;

        void load();
        void unload();
        void setData(const std::string& data);
        void setGL(GladGLContext* GL);

        const unsigned char* getData() const;
        const GladGLContext* getGL() const;
        unsigned int getID() const;
        unsigned int getWidth() const;
        unsigned int getHeight() const;
    };
}
