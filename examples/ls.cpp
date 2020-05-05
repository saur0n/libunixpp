/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Example: list files in a directory
 *  
 *  © 2020, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include <iostream>
#include <unix++/Directory.hpp>

using namespace nx;
using std::cerr;
using std::cout;
using std::endl;

static void ls(const char * path) {
    Directory directory(path);
    cout << path << ":\n";
    while (Directory::Entry * entry=directory.read())
        cout << "    " << entry->d_name << endl;
}

int main(int argc, char ** argv) {
    setlocale(LC_ALL, "");
    
    for (int i=1; i<argc; i++) {
        try {
            ls(argv[i]);
        }
        catch (const std::exception &e) {
            cerr << argv[i] << ": " << e.what() << endl;
        }
    }
    
    return 0;
}
