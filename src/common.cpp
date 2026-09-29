#include "include/common.hpp"


using std::cout;
using std::endl;
using std::string;

int parseArguments(int argc, char *argv[], fs::path src , fs::path dst) {

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
            } else {

                params.should_compress = false;

            }

        }
        else continue;

        // If we should compress, run the compressing code using the is_os() functions defined in include/os.hpp
        if(params.should_compress) {

            // Linux/MacOS/POSIX code
            if(is_linux() || is_mac() || is_posix()) {

                syncFolders(src, dst);

                std::string cmd = "zip -r zipped.zip \"" + dst.string() + "\"";
                int result = std::system(cmd.c_str());

                if(result != 0) {

                    std::cerr << "Failed to zip the folder!\n"; 
                    
                }

                cmd = "rm -rf \"" + dst.string() + "\"";
                std::system(cmd.c_str());

                return 0;

            // Windows code(same as Linux/MacOS/POSIX one)
            } else if(is_windows()) {

                syncFolders(src, dst);

                std::string cmd = "powershell -Command \"Compress-Archive -Path '" + dst.string() + "\\*' -DestinationPath 'zipped.zip' -Force\"";
                int result = std::system(cmd.c_str());

                if(result != 0) {
                    std::cerr << "Failed to zip the folder!\n"; 
                }

                cmd = "rmdir /s /q \"" + dst.string() + "\"";
                std::system(cmd.c_str());

                return 0;

            // Else we return an error since the OS is unknown
            } else {

                cout << "Unknown OS, could not fire ZIP operation" << endl;
                return 1;

            }

            return 0;
        }
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
    cout <<  "Wrong Usage:" << endl;
    cout <<  "Usage: sync [path/to/folder/1] [path/to/folder/2]" << endl;
    cout <<  "PS: Folder1 is the one that gets backuped to Folder2. Therefore Folder1 must exist and mustn't be empty" << endl;

}

void syncFolders(const fs::path &src, const fs::path &dst) {

    /*
    Functions to sync the folders, writing it in main would bloat the code.
    This will check for already upto-date files with the size.
    */

    int copied = 0; 
    int upToDate = 0;

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