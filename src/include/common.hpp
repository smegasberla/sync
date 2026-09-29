#ifndef COMMON_HPP
#define COMMON_HPP

#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <cstdlib>
#include <cstring>

std::string const FSYNC_VERSION = "1.0.2";

namespace fs = std::filesystem;

typedef struct ParamBools {
    bool should_compress = false;
    bool send_help = false;
    bool send_version = false;
} ParamBools;

void sendUsage();
void sendVersion();
int syncFolders(const fs::path src, fs::path dst, bool execute);

int parseArguments(int argc, char *argv[], 
                   std::optional<fs::path> src = std::nullopt, 
                   std::optional<fs::path> dst = std::nullopt);

#endif // COMMON_HPP