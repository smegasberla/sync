#ifndef COMMON_HPP
#define COMMON_HPP

#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "os.hpp"

namespace fs = std::filesystem;

typedef struct ParamBools {

    bool should_compress = false;

}  ParamBools;

void sendUsage();
void syncFolders(const fs::path &src, const fs::path &dst);
int parseArguments(int argc, char *argv[], fs::path src ,fs::path dst); 

#endif // MY_HEADER_HPP