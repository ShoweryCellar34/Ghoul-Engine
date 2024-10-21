#include <resourceManager.hpp>

#include <Pentagram.hpp>

namespace GH {
    // Resource definitions.

    resource::resource(const fs::path& path) {
        fs::file_status status = fs::status(path);
        if(fs::is_directory(path)) {
            throw "Path \"" + path.string() + "\" is not a file path.";
        }
        if(!fs::exists(path)) {
            m_handle.open(path, std::ios::out);
            m_handle.close();
        }
        m_handle.open(path, std::ios::out | std::ios::in);
        if(!m_handle.is_open()) {
            std::string message = "File \"" + path.string() + "\" failed to open, this could mean the file is already in use or cannot be opened.";
            throw message.c_str();
        }
        m_path = path;
        m_filename = path.filename();
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
        m_handle.write(data, strlen(data));
    }

    std::string resource::getData() const {
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

    // ResourceManager definitions.

    resourceManager::resourceManager() : m_resources() {
    }

    bool resourceManager::exists(const std::string& alias) {
        if(m_resources.find(alias) != m_resources.end()) {
            return true;
        } else {
            return false;
        }
    }

    void resourceManager::flush(const std::string& alias) {
        if(m_resources.find(alias) == m_resources.end()) {
            throw "Alias \"" + (std::string)alias + "\" is not registered.";
        }
        m_resources.at(alias).get()->flush();
    }

    void resourceManager::write(const std::string& alias, const std::string& data) {
        if(m_resources.find(alias) == m_resources.end()) {
            throw "Alias \"" + (std::string)alias + "\" is not registered.";
        }
        m_resources.at(alias).get()->write(data.c_str());
    }

    std::shared_ptr<resource> resourceManager::loadResource(const std::string& alias, fs::path path) {
        if(m_resources.find(alias) != m_resources.end()) {
            throw "Alias \"" + (std::string)alias + "\" is already registered.";
        }
        std::shared_ptr<resource> newResource = std::make_shared<resource>(path);
        m_resources.insert({alias, newResource});
        return newResource;
    }

    void resourceManager::unloadResource(const std::string& alias) {
        if(m_resources.find(alias) == m_resources.end()) {
            throw "Alias \"" + (std::string)alias + "\" is not registered.";
        }
        m_resources.erase(alias);
    }

    std::shared_ptr<resource> resourceManager::getResource(const std::string& alias) const {
        if(m_resources.find(alias) == m_resources.end()) {
            throw "Alias \"" + (std::string)alias + "\" is not registered, maybe you haven't loaded it yet.";
        }
        return m_resources.at(alias);
    }

    std::string resourceManager::getData(const std::string& alias) const {
        if(m_resources.find(alias) == m_resources.end()) {
            throw "Alias \"" + (std::string)alias + "\" is not registered.";
        }
        return m_resources.at(alias).get()->getData();
    }

    fs::path resourceManager::getFilename(const std::string& alias) const {
        if(m_resources.find(alias) == m_resources.end()) {
            throw "Alias \"" + (std::string)alias + "\" is not registered.";
        }
        return m_resources.at(alias).get()->getFilename();
    }

    fs::path resourceManager::getRelativePath(const std::string& alias) const {
        if(m_resources.find(alias) == m_resources.end()) {
            throw "Alias \"" + (std::string)alias + "\" is not registered.";
        }
        return m_resources.at(alias).get()->getRelativePath();
    }

    fs::path resourceManager::getAbsolutePath(const std::string& alias) const {
        if(m_resources.find(alias) == m_resources.end()) {
            throw "Alias \"" + (std::string)alias + "\" is not registered.";
        }
        return m_resources.at(alias).get()->getAbsolutePath();
    }
}
