#pragma once

#include <memory>
#include <fstream>
#include <filesystem>

struct node;
typedef node* nodeRef;
typedef std::shared_ptr<std::fstream> fileHandle;
typedef std::filesystem::path filePath;
