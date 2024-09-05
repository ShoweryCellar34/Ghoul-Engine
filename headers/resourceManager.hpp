#pragma once

#include <unordered_map>
#include <fstream>
#include <filesystem>
#include <defines.hpp>

class resource {
private:
    std::fstream m_handle;
    std::filesystem::path m_path;
    std::string m_fileName;
    std::string m_reference;

public:
    resource(const char* path);
    ~resource();
};
