#include "include/common.hpp"
#include "args/include/compress.hpp"
#include <optional>
#include <iostream>


using std::cout;
using std::endl;
using std::string;

int parseArguments(int argc, char *argv[], std::optional<fs::path> src, std::optional<fs::path> dst) {

    /*
    Small engine to parse eventual arguments.
    */

    ParamBools params;
    // Looping trough the arguments
    for (int i = 1; i < argc; i++) {

        std::string arg = argv[i];
        std::string argInit = "--";

        // Finding parts in the command that start with --
        if (arg.rfind(argInit) == 0) {

            // If we find compress , set --compress to true, false otherwise.
            if(strcmp(arg.c_str(), "--compress") == 0) {

                params.should_compress = true;
            }

            if(strcmp(arg.c_str(), "--help") == 0) {

                params.send_help = true;

            }

            if(strcmp(arg.c_str(), "--version") == 0) {

                params.send_version = true;

            }

        }
        else continue;
    }

    // Handle flags in order of priority
    if (params.send_help) {

        sendUsage();
        return 0;

    }

    if (params.send_version) {

        sendVersion();
        return 0;

    }

    // If we should compress, run the compressing code using the is_os() functions defined in include/os.hpp
    if (params.should_compress) {

        if(src.has_value() && dst.has_value()) {

            compress(src.value(), dst.value());
            return 0;

        } else return -2;

    }

    /*
    Here returning -1
    Without this, if we didnt have an argument, we would never have the basic functionality, is a lazy fix, but it will do for now :)
    */

    return -1;
}

void sendUsage() {

    /*
    Simple function to send the usage on call, printing it with cout.
    Why: It would be a pain to write this all the time LOL.
    */
    cout << "========================================================\n";
    cout << "                 Fsync help message                     \n";
    cout << "========================================================\n\n";
    cout << "Version: " << FSYNC_VERSION << "\n";
    cout << "Usage:\n";
    cout << "  fsync <source_dir> <destination_dir> [options]\n\n";
    cout << "Arguments:\n";
    cout << "  <source_dir>        Path to the folder you want to back up.\n";
    cout << "                      (Must exist and cannot be empty)\n";
    cout << "  <destination_dir>   Path where files will be synchronized.\n";
    cout << "                      (Will be created if it does not exist)\n\n";
    cout << "Options:\n";
    cout << "  --compress          Compresses the synchronized destination\n";
    cout << "                      directory into 'zipped.zip' and cleans up\n";
    cout << "                      the temporary folder afterwards.\n";
    cout << "  --help              Display this help message and exit.\n\n";
    cout << "Examples:\n";
    cout << "  fsync ./my_folder ./backup_folder\n";
    cout << "  fsync ./my_folder ./backup_folder --compress\n";
    cout << "========================================================\n";
}

void sendVersion() {

    cout << "Fsync version: " << endl;
    cout << FSYNC_VERSION << endl;

}


int syncFolders(const fs::path src, const fs::path dst, bool execute) {

    /*
    Functions to sync the folders, writing it in main would bloat the code.
    This will check for already upto-date files with the size.
    */

    int copied = 0; 
    int upToDate = 0;

    std::string srcStr = src.string();
    std::string dstStr = dst.string();
    
    if(execute == false) {

        return -1;

    }

    if (srcStr.rfind("--") == 0 || dstStr.rfind("--") == 0) {

        return -1;

    }

    // Looping trough the directory of the first folder recurseverly
    for(auto &entry : fs::recursive_directory_iterator(src)) {

        // Checking if its not a regular file
        // Why: By doing this, we prevent creating files, instead we only create the needed dirs
        if(!entry.is_regular_file()) {

            fs::create_directories(entry);
            continue;

        }


        fs::path rel = entry.path().relative_path();
        fs::path target = dst / rel;

        // Checking if a copy is needed by checking file existance and comparing the sixe of the entry to the target file
        bool needsCopy = !fs::exists(target) || fs::file_size(entry.path()) != fs::file_size(target);

        // Checking if it needs a copy
        if(needsCopy) {

            /*
            Creating directories first in the target folder
            Why: Without this, copy doesent create the folders automatically, and the program would never work :(
            */
            fs::create_directories(target.parent_path());
            fs::copy(entry.path(), target);
            copied++;

        } else upToDate++; // If doesent need copy, its up to date so we just increase the variable

    }

    // Printing final message
    cout << "Total Files: " << copied + upToDate << endl;
    cout << "Copied Files: " << copied << endl;
    cout << "Up To Date Files: " << upToDate << endl;
    cout << "Copy is successful! " << endl;

}