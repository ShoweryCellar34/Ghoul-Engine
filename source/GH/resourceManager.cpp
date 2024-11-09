#include <GH/resourceManager.hpp>

#include <PNT/Pentagram.hpp>
#include <GH/error.hpp>

namespace GH::resources {
    // Perms definitions

    perms::perms() : m_read(false), m_write(false) {
    }

    perms::perms(bool read, bool write) : m_read(read), m_write(write) {
    }

    std::ios_base::openmode perms::toOpenmode() const {
        std::ios_base::openmode result = (std::ios_base::openmode)0;
        if(m_read) {
            result |= std::ios::in;
        }
        if(m_write) {
            result |= std::ios::out;
        }
        return result;
    }

    namespace internal {
        // Resource definitions.

        resource::resource(const fs::path& path, perms permitions, bool mustExist) {
            if(!fs::exists(path) && !mustExist) {
                m_handle.open(path, std::ios::out);
                m_handle.close();
            } else if(!fs::exists(path) && mustExist) {
                throw error::exception("Path \"" + path.string() + "\" does not exist, if you want to create a file pass false as the last agument.");
            }
            if(fs::is_directory(path)) {
                throw "Path \"" + path.string() + "\" is not a file path.";
            }

            m_handle.open(path, permitions.toOpenmode());
            if(!m_handle.is_open()) {
                throw error::exception("File \"" + path.string() + "\" failed to open, this could mean the file is already in use or cannot be opened.");
            }
            m_path = path;
            m_filename = path.filename();
            m_permitions = permitions;
        }

        resource::~resource() {
            flush();
            if(m_handle.is_open()) {
                m_handle.close();
            }
        }

        void resource::flush() {
            m_handle.flush();
        }

        void resource::write(const char* data) {
            if(!m_permitions.m_write) {
                throw error::exception("File \"" + m_path.string() + " has writting disabled.");
            }
            m_handle.write(data, strlen(data));
        }

        std::string resource::getData() const {
            if(!m_permitions.m_read) {
                throw error::exception("File \"" + m_path.string() + " has reading disabled.");
            }
            m_handle.seekg(0, std::ios::end);
            std::streamsize fileSize = m_handle.tellg();
            m_handle.seekg(0, std::ios::beg);

            std::string buf(fileSize, '\0');

            m_handle.read(&buf[0], fileSize);
            return buf;
        }

        fs::path resource::getFilename() const {
            return m_filename;
        }

        fs::path resource::getRelativePath() const {
            return fs::relative(m_path);
        }

        fs::path resource::getAbsolutePath() const {
            return fs::absolute(m_path);
        }

        perms resource::getPermitions() const {
            return m_permitions;
        }

        // ResourceManager definitions.

        resourceManager::~resourceManager() {
            for(const std::pair<const std::string&, const resource*> resource : m_resources) {
                delete resource.second;
            }
        }

        bool resourceManager::loaded(const std::string& alias) {
            if(m_resources.find(alias) != m_resources.end()) {
                return true;
            } else {
                return false;
            }
        }

        void resourceManager::flush(const std::string& alias) {
            if(m_resources.find(alias) == m_resources.end()) {
                throw error::exception("Alias \"" + alias + "\" is not registered.");
            }
            m_resources.at(alias)->flush();
        }

        void resourceManager::write(const std::string& alias, const std::string& data) {
            if(m_resources.find(alias) == m_resources.end()) {
                throw error::exception("Alias \"" + alias + "\" is not registered.");
            }
            m_resources.at(alias)->write(data.c_str());
        }

        resource* resourceManager::loadResource(const std::string& alias, const fs::path& path, perms permitions, bool mustExist) {
            if(!(permitions.m_read) && !(permitions.m_write)) {
                throw error::exception("Permitions cannot be unradable and unwritable");
            }
            if(m_resources.find(alias) != m_resources.end()) {
                throw error::exception("Alias \"" + alias + "\" is already registered.");
            }
            resource* newResource = new resource(path, permitions, mustExist);
            m_resources.insert({alias, newResource});
            return newResource;
        }

        void resourceManager::unloadResource(const std::string& alias) {
            if(m_resources.find(alias) == m_resources.end()) {
                throw error::exception("Alias \" + alias + \" is not registered.");
            }
            delete m_resources.at(alias);
            m_resources.erase(alias);
        }

        resource* resourceManager::getResource(const std::string& alias) const {
            if(m_resources.find(alias) == m_resources.end()) {
                throw error::exception("Alias \"" + alias + "\" is not registered, maybe you haven't loaded it yet.");
            }
            return m_resources.at(alias);
        }

        std::string resourceManager::getData(const std::string& alias) const {
            if(m_resources.find(alias) == m_resources.end()) {
                throw error::exception("Alias \"" + alias + "\" is not registered.");
            }
            return m_resources.at(alias)->getData();
        }

        fs::path resourceManager::getFilename(const std::string& alias) const {
            if(m_resources.find(alias) == m_resources.end()) {
                throw error::exception("Alias \"" + alias + "\" is not registered.");
            }
            return m_resources.at(alias)->getFilename();
        }

        fs::path resourceManager::getRelativePath(const std::string& alias) const {
            if(m_resources.find(alias) == m_resources.end()) {
                throw error::exception("Alias \"" + alias + "\" is not registered.");
            }
            return m_resources.at(alias)->getRelativePath();
        }

        fs::path resourceManager::getAbsolutePath(const std::string& alias) const {
            if(m_resources.find(alias) == m_resources.end()) {
                throw error::exception("Alias \"" + alias + "\" is not registered.");
            }
            return m_resources.at(alias)->getAbsolutePath();
        }
    }
}
