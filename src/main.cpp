#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <fstream>

// Using declarations
using std::cout;
using std::endl;
using std::string;

// Namespace declarations
namespace fs = std::filesystem;

// Function declarations
void sendUsage();
void syncFolders(const fs::path &src, const fs::path &dst);

int main(int argc, char* argv[]) {

    // Checking for arguments and usage 
    if(argc != 3) {

        sendUsage();
        return 1;

    }

    /*
    Taking the first folder
    We first check if it exists and if it is a directory, we throw an error and return otherwhise
    */
    const fs::path src = argv[1];
    if (!fs::exists(src) || !fs::is_directory(src)) {

        cout << "The first argument isnt a folder or doesent exist on disk." << endl;
        sendUsage();
        return 2;
    }
    /*
    Here i check if the src folder is empty
    Why: Why even use the program if the src folder is empty LOL
    */
    if (fs::is_empty(src)) {

        cout << "The first folder is empty, there is nothing to backup!" << endl;
        sendUsage();
        return 3;
    
    }

    /*
    Taking second folder
    Falling back to creating it if it doesent exist
    */
    const fs::path dst = argv[2];
    if (!fs::exists(dst)) {
    
        fs::create_directory(dst);

    }

    // We sync the folders and return, thats it!  
    syncFolders(src, dst);
    return 0;

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