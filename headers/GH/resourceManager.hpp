#pragma once

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <string>

namespace fs = std::filesystem;

namespace GH::resources {
    struct perms {
        bool m_read;
        bool m_write;

        perms();
        perms(bool read, bool write);

        std::ios_base::openmode toOpenmode() const;
    };

    namespace internal {
        class resource {
        private:
            mutable std::fstream m_handle;
            fs::path m_path;
            fs::path m_filename;
            perms m_permitions;

        public:
            resource(const fs::path& path, perms permitions = perms(true, false), bool mustExist = true);
            ~resource();
            resource(const resource&) = delete;
            resource& operator=(const resource&) = delete;

            void flush();
            void write(const char* data);

            std::string getData() const;
            fs::path getFilename() const;
            fs::path getRelativePath() const;
            fs::path getAbsolutePath() const;
            perms getPermitions() const;
        };

        class resourceManager {
        private:
            std::unordered_map<std::string, resource*> m_resources;

        public:
            resourceManager() = default;
            ~resourceManager();
            resourceManager(const resourceManager&) = delete;
            resourceManager& operator=(const resourceManager&) = delete;

            bool loaded(const std::string& alias);
            void flush(const std::string& alias);
            void write(const std::string& alias, const std::string& data);
            resource* loadResource(const std::string& alias, const fs::path& path, perms permitions = perms(true, false), bool mustExist = true);
            void unloadResource(const std::string& alias);

            resource* getResource(const std::string& alias) const;
            std::string getData(const std::string& alias) const;
            fs::path getFilename(const std::string& alias) const;
            fs::path getRelativePath(const std::string& alias) const;
            fs::path getAbsolutePath(const std::string& alias) const;
        };
    }
}
