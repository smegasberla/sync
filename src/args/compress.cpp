#include "../include/os.hpp"
#include "../include/common.hpp"
#include "include/compress.hpp"

using std::cout;
using std::endl;
using std::string;


int compress(fs::path src, fs::path dst) {

    /*
    Compression logic moved to an appropriate file.
    */

    // Linux/MacOS/POSIX code
    if(is_linux() || is_mac() || is_posix()) {

        syncFolders(src, dst, true);

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

        syncFolders(src, dst, true);

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

