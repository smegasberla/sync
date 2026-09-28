#pragma once

/*
Keeping those here as example

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#endif

#if defined(__linux__)
    #include <unistd.h>
#endif

*/

// Compile-time platform checks
constexpr bool is_windows() {
    #if defined(_WIN32) || defined(_WIN64)
        return true;
    #else
        return false;
    #endif
}

constexpr bool is_mac() {
    #if defined(__APPLE__) || defined(__MACH__)
        return true;
    #else
        return false;
    #endif
}

constexpr bool is_linux() {
    #if defined(__linux__)
        return true;
    #else
        return false;
    #endif
}

constexpr bool is_posix() {
    #if defined(__unix__) || defined(__POSIX__) || defined(__APPLE__)
        return true;
    #else
        return false;
    #endif
}