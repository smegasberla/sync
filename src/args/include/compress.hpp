#ifndef COMPRESS_HPP
#define COMPRESS_HPP

#include <filesystem>

namespace fs = std::filesystem;

int compress(fs::path src, fs::path dst);

#endif