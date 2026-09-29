#include <cstring>
#include <iostream>
#include <filesystem>
#include <string>
#include "include/os.hpp"
#include "include/common.hpp"

// Using declarations
using std::cout;
using std::endl;
using std::string;

// Namespace declarations
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

    if (argc >= 2) {
        std::string firstArg = argv[1];
        if (firstArg == "--help" || firstArg == "--version") {
            parseArguments(argc, argv, std::nullopt, std::nullopt);
            return 0; 
        }
    }

    if(argc < 3) 
        sendUsage();
        return 2;

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
    int result = parseArguments(argc, argv, src, dst);
    
    if(result == 0) 
        return 0;
    else
        syncFolders(src, dst, true);
    
    return 0;

}

