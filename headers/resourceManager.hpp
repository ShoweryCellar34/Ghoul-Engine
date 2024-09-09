#pragma once

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <memory>
#include <defines_and_globals.hpp>

namespace fs = std::filesystem;

class resource {
private:
    mutable std::fstream m_handle;
    fs::path m_path;
    fs::path m_filename;

public:
    resource(const fs::path& path);
    ~resource();
    resource(const resource&) = delete;
    resource& operator=(const resource&) = delete;

    void flush();
    void write(const char* data);

    std::string getData() const;
    fs::path getFilename() const;
    fs::path getRelativePath() const;
    fs::path getAbsolutePath() const;
};

class resourceManager {
private:
    std::unordered_map<std::string, std::shared_ptr<resource>> m_resources;

public:
    resourceManager();
    resourceManager(const resourceManager&) = delete;
    resourceManager& operator=(const resourceManager&) = delete;

    std::shared_ptr<resource> getResource(const char* alias) const;
    void flush(const char* alias);
    void write(const char* alias, const char* data);

    std::shared_ptr<resource> loadResource(fs::path path, const char* alias);
    void unloadResource(const char* alias);
    std::string getData(const char* alias) const;
    fs::path getFilename(const char* alias) const;
    fs::path getRelativePath(const char* alias) const;
    fs::path getAbsolutePath(const char* alias) const;
};
