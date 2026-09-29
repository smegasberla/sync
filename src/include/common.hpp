#ifndef COMMON_HPP
#define COMMON_HPP

#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

std::string const FSYNC_VERSION = "1.0.1";

namespace fs = std::filesystem;

typedef struct ParamBools {

    bool should_compress = false;
    bool send_help = false;
    bool send_version = false;

}  ParamBools;

void sendUsage();
void sendVersion();
int syncFolders(const fs::path &src, const fs::path &dst, bool execute);
int parseArguments(int argc, char *argv[], fs::path src ,fs::path dst); 

#endif // MY_HEADER_HPP