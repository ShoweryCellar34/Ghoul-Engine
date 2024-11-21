#include <GH/cpp/textureManager.hpp>

#include <stb_image.h>
#include <GH/cpp/error.hpp>

namespace GH::renderer {
    namespace internal {
        // Texture definitions

        texture::texture() : m_GL(nullptr), m_ID(0), m_width(0), m_height(0), m_channels(0), m_rawData(nullptr) {
        }

        texture::texture(GladGLContext* GL, const std::string& data) : m_GL(GL), m_ID(0) {
            m_rawData = stbi_load_from_memory((unsigned char*)data.c_str(), data.size(), &m_width, &m_height, &m_channels, 4);

            if(!m_GL) {
                throw error::exception("OpenGL context is null.");
            }
            if(m_ID) {
                throw error::exception("Image is already loaded with ID: " + std::to_string(m_ID) + ".");
            }
            if(!m_rawData) {
                throw error::exception("Data for image is null.");
            }

            m_GL->GenTextures(1, &m_ID);
            m_GL->BindTexture(GL_TEXTURE_2D, m_ID);
            m_GL->TexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_rawData);
            m_GL->GenerateMipmap(GL_TEXTURE_2D);
            m_GL->BindTexture(GL_TEXTURE_2D, 0);
        }

        texture::~texture() {
            m_GL->DeleteTextures(1, &m_ID);
            m_ID = 0;

            if(m_rawData != nullptr) {
                stbi_image_free(m_rawData);
            }
        }

        std::string texture::getData() const {
            return m_data;
        }

        unsigned char* const texture::getRawData() const {
            return m_rawData;
        }

        const GladGLContext* const texture::getGL() const {
            return m_GL;
        }

        unsigned int texture::getID() const {
            return m_ID;
        }

        int texture::getWidth() const {
            return m_width;
        }

        int texture::getHeight() const {
            return m_height;
        }

        // TextureManager definitions

        textureManager::~textureManager() {
            for(const std::pair<const std::string&, const texture*> texture : m_textures) {
                delete texture.second;
            }
        }

        bool textureManager::loaded(const std::string& alias) {
            if(m_textures.find(alias) != m_textures.end()) {
                return true;
            } else {
                return false;
            }
        }

        texture* textureManager::loadTexture(const std::string& alias, const std::string& data) {
            if(m_textures.find(alias) != m_textures.end()) {
                throw error::exception("Texture alias \"" + alias + "\" is already registered.");
            }
            texture* newtexture = new texture(m_GL, data);
            m_textures.insert({alias, newtexture});
            return newtexture;
        }

        void textureManager::unloadTexture(const std::string& alias) {
            if(m_textures.find(alias) == m_textures.end()) {
                throw error::exception("Texture alias \"" + alias + "\" is not registered.");
            }
            delete m_textures.at(alias);
            m_textures.erase(alias);
        }

        void textureManager::setGL(GladGLContext* GL) {
            std::unordered_map<std::string, std::string> textureData;
            for(std::pair<std::string, texture*> texture : m_textures) {
                textureData.insert({texture.first, texture.second->getData()});
                unloadTexture(texture.first);
            }
            m_GL = GL;
            for(std::pair<std::string, std::string> data : textureData) {
                loadTexture(data.first, data.second);
            }
        }

        texture* textureManager::getTexture(const std::string& alias) const {
            if(m_textures.find(alias) == m_textures.end()) {
                throw error::exception("Texture alias \"" + alias + "\" is not registered, maybe you haven't loaded it yet.");
            }
            return m_textures.at(alias);
        }

        std::string textureManager::getData(const std::string& alias) const {
            if(m_textures.find(alias) == m_textures.end()) {
                throw error::exception("Texture alias \"" + alias + "\" is not registered.");
            }
            return m_textures.at(alias)->getData();
        }

        unsigned char* const textureManager::getRawData(const std::string& alias) const {
            if(m_textures.find(alias) == m_textures.end()) {
                throw error::exception("Texture alias \"" + alias + "\" is not registered.");
            }
            return m_textures.at(alias)->getRawData();
        }

        int textureManager::getWidth(const std::string& alias) const {
            if(m_textures.find(alias) == m_textures.end()) {
                throw error::exception("Texture alias \"" + alias + "\" is not registered.");
            }
            return m_textures.at(alias)->getWidth();
        }

        int textureManager::getHeight(const std::string& alias) const {
            if(m_textures.find(alias) == m_textures.end()) {
                throw error::exception("Texture alias \"" + alias + "\" is not registered.");
            }
            return m_textures.at(alias)->getHeight();
        }
    }
}
