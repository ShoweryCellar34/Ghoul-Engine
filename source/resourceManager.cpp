#include "resourceManager.hpp"

#include <cstring>
#include <Pentagram.hpp>

// Global resourceManager.

resourceManager g_resourceManager;

// Resource definitions.

resource::resource(const fs::path& path) {
    fs::file_status status = fs::status(path);
    if(!fs::is_directory(path)) {
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
    } else {
        std::string message = "Path \"" + path.string() + "\" is not a file path.";
        throw std::exception(message.c_str());
    }
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

std::shared_ptr<resource> resourceManager::getResource(const char *alias) const
{
    if(m_resources.find(alias) != m_resources.end()) {
        return m_resources.at(alias);
    } else {
        std::string message = "Alias \"" + (std::string)alias + "\" is not registered, maybe you haven't loaded it yet.";
        throw std::exception(message.c_str());
    }
}

void resourceManager::flush(const char* alias) {
    if(m_resources.find(alias) != m_resources.end()) {
        m_resources.at(alias).get()->flush();
    } else {
        std::string message = "Alias \"" + (std::string)alias + "\" is not registered.";
        throw message.c_str();
    }
}

void resourceManager::write(const char* alias, const char* data) {
    if(m_resources.find(alias) != m_resources.end()) {
        m_resources.at(alias).get()->write(data);
    } else {
        std::string message = "Alias \"" + (std::string)alias + "\" is not registered.";
        throw message.c_str();
    }
}

std::shared_ptr<resource> resourceManager::loadResource(fs::path path, const char* alias) {
    if(m_resources.find(alias) == m_resources.end()) {
        std::shared_ptr<resource> newResource = std::make_shared<resource>(path);
        m_resources.insert({alias, newResource});
        return newResource;
    } else {
        std::string message = "Alias \"" + (std::string)alias + "\" is already registered.";
        throw message.c_str();
    }
}

void resourceManager::unloadResource(const char* alias) {
    if(m_resources.find(alias) != m_resources.end()) {
        m_resources.erase(alias);
    } else {
        std::string message = "Alias \"" + (std::string)alias + "\" is not registered.";
        throw message.c_str();
    }
}

std::string resourceManager::getData(const char* alias) const {
    if(m_resources.find(alias) != m_resources.end()) {
        return m_resources.at(alias).get()->getData();
    } else {
        std::string message = "Alias \"" + (std::string)alias + "\" is not registered.";
        throw message.c_str();
    }
}

fs::path resourceManager::getFilename(const char* alias) const {
    if(m_resources.find(alias) != m_resources.end()) {
        return m_resources.at(alias).get()->getFilename();
    } else {
        std::string message = "Alias \"" + (std::string)alias + "\" is not registered.";
        throw message.c_str();
    }
}

fs::path resourceManager::getRelativePath(const char* alias) const {
    if(m_resources.find(alias) != m_resources.end()) {
        return m_resources.at(alias).get()->getRelativePath();
    } else {
        std::string message = "Alias \"" + (std::string)alias + "\" is not registered.";
        throw message.c_str();
    }
}

fs::path resourceManager::getAbsolutePath(const char* alias) const {
    if(m_resources.find(alias) != m_resources.end()) {
        return m_resources.at(alias).get()->getAbsolutePath();
    } else {
        std::string message = "Alias \"" + (std::string)alias + "\" is not registered.";
        throw message.c_str();
    }
}
