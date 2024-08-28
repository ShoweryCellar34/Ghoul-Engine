#pragma once

#include <unordered_map>
#include <fstream>

class resourceManager {
private:
    std::unordered_map<std::fstream, const char*> handles;

public:
    resourceManager();
    ~resourceManager();
};
