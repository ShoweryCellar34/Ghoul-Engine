#pragma once

#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <defines.hpp>

namespace fs = std::filesystem;

class resource {
private:
    std::fstream m_handle;
    fs::path m_path;
    fs::path m_filename;

public:
    resource(const fs::path& path);
    ~resource();

    void flush();
    void write(const char* data);

    std::string getData();
    fs::path getFilename() const;
    fs::path getRelativePath() const;
    fs::path getAbsolutePath() const;
};
