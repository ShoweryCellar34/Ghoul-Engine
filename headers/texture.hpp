#pragma once

#include <cstdint>

namespace GH {
    class texture {
    private:
        size_t m_ID, m_width, m_height;
        unsigned char* m_data;

    public:
        texture();
        texture(unsigned char* data, size_t width, size_t height);
        texture(const texture&) = delete;
        texture& operator=(const texture&) = delete;
    };
}
