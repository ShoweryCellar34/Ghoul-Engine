#pragma once

#include <string>
#include <unordered_map>
#include <glad/gl.h>
#include <GH/cpp/globalsAndDefines.hpp>

namespace GH::renderer {
    namespace internal {
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

        class textureManager {
        private:
            std::unordered_map<std::string, texture*> m_textures;

        public:
            textureManager() = default;
            ~textureManager();
            textureManager(const textureManager&) = delete;
            textureManager& operator=(const textureManager&) = delete;

            bool loaded(const std::string& alias);
            texture* loadResource(const std::string& alias, const std::string& data);
            void unloadResource(const std::string& alias);

            texture* getResource(const std::string& alias) const;
            std::string getData(const std::string& alias) const;
        };
    }
}
