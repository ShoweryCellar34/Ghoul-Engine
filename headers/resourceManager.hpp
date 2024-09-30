#pragma once

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <string>
#include <defines_and_globals.hpp>

namespace GH {
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

        std::shared_ptr<resource> getResource(std::string alias) const;
        void flush(std::string alias);
        void write(std::string alias, std::string data);

        std::shared_ptr<resource> loadResource(std::string alias, fs::path path);
        void unloadResource(std::string alias);
        std::string getData(std::string alias) const;
        fs::path getFilename(std::string alias) const;
        fs::path getRelativePath(std::string alias) const;
        fs::path getAbsolutePath(std::string alias) const;
    };
}
