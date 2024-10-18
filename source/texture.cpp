#include <texture.hpp>

#include <cstring>
#include <format>
#include <stb_image.h>

namespace GH {
    texture::texture() : m_GL(nullptr), m_ID(0), m_width(0), m_height(0), m_channels(0), m_data(nullptr) {
    }

    texture::texture(GladGLContext* GL, const std::string& data) : m_GL(GL), m_ID(0) {
        m_data = stbi_load_from_memory((unsigned char*)data.c_str(), data.size(), (int*)&m_width, (int*)&m_height, (int*)&m_channels, 4);
    }

    texture::~texture() {
        if(m_data != nullptr) {
            stbi_image_free(m_data);
        }
    }

    void texture::load() {
        if(!m_GL) {
            throw "OpenGL context is null.";
        }
        if(m_ID) {
            throw std::format("Image is already loaded with ID: {}.", m_ID);
        }
        if(!m_data) {
            throw "Data for image is null.";
        }

        m_GL->GenTextures(1, &m_ID);
        m_GL->BindTexture(GL_TEXTURE_2D, m_ID);
        m_GL->TexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
        m_GL->GenerateMipmap(GL_TEXTURE_2D);
        m_GL->BindTexture(GL_TEXTURE_2D, 0);
    }

    void texture::unload() {
        if(!m_GL) {
            throw "OpenGL context is null.";
        }
        if(!m_ID) {
            throw "Image is not loaded.";
        }

        m_GL->DeleteTextures(1, &m_ID);
        m_ID = 0;
    }

    void texture::setData(const std::string& data) {
        if(m_ID) {
            throw std::format("Image loaded with ID: {}.", m_ID);
        }

        if(m_data != nullptr) {
            stbi_image_free(m_data);
        }

        m_data = stbi_load_from_memory((unsigned char*)data.c_str(), data.size(), (int*)&m_width, (int*)&m_height, (int*)&m_channels, 4);
    }

    void texture::setGL(GladGLContext* GL) {
        if(m_ID) {
            throw std::format("Image loaded with ID: {}.", m_ID);
        }

        m_GL = GL;
    }

    const unsigned char* texture::getData() {
        return m_data;
    }

    const GladGLContext* texture::getGL() {
        return m_GL;
    }

    unsigned int texture::getID() {
        return m_ID;
    }

    unsigned int texture::getWidth() {
        return m_width;
    }

    unsigned int texture::getHeight() {
        return m_height;
    }
}
