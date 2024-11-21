#include <GH/cpp/textureManager.hpp>

#include <stb_image.h>
#include <GH/cpp/error.hpp>

namespace GH::renderer {
    namespace internal {
        // Texture definitions

        texture::texture() : m_GL(nullptr), m_ID(0), m_width(0), m_height(0), m_channels(0), m_data(nullptr) {
        }

        texture::texture(GladGLContext* GL, const std::string& data) : m_GL(GL), m_ID(0) {
            m_data = stbi_load_from_memory((unsigned char*)data.c_str(), data.size(), &m_width, &m_height, &m_channels, 4);
        }

        texture::~texture() {
            if(m_data != nullptr) {
                stbi_image_free(m_data);
            }
        }

        const unsigned char* const texture::getData() const {
            return m_data;
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

        texture* textureManager::getTexture(const std::string& alias) const {
            if(m_textures.find(alias) == m_textures.end()) {
                throw error::exception("Texture alias \"" + alias + "\" is not registered, maybe you haven't loaded it yet.");
            }
            return m_textures.at(alias);
        }

        const unsigned char* const textureManager::getData(const std::string& alias) const {
            if(m_textures.find(alias) == m_textures.end()) {
                throw error::exception("Texture alias \"" + alias + "\" is not registered.");
            }
            return m_textures.at(alias)->getData();
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
