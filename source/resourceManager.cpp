#include "resourceManager.hpp"

#include <cstring>
#include <Pentagram.hpp>

resource::resource(const fs::path& path) {
    fs::file_status status = fs::status(path);
    if(!fs::is_directory(path)) {
        m_handle.open(path);
        m_path = path;
        m_filename = path.filename();
    } else {
        std::string message = "[FMGR]Path \"" + path.string() + "\" is not a file path, aborting operation.";
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

std::string resource::getData() {
    m_handle.seekg(0, std::ios::end);
    std::streamsize fileSize = m_handle.tellg();
    m_handle.seekg(0, std::ios::beg);

    std::string buf(fileSize, '\0');

    m_handle.read(&buf[0], fileSize);
    return buf;
}

fs::path resource::getFilename() const
{
    return m_filename;
}

fs::path resource::getRelativePath() const {
    return fs::relative(m_path);
}

fs::path resource::getAbsolutePath() const {
    return fs::absolute(m_path);
}
