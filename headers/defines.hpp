#pragma once

#include <memory>
#include <fstream>

struct node;
typedef node* nodeRef;
typedef std::shared_ptr<std::fstream> fileHandle;
