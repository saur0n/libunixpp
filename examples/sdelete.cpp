/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Example: secure file deleter
 *  
 *  © 2020, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include <algorithm>
#include <iostream>
#include <locale.h>
#include <unix++/File.hpp>

using nx::File;
using std::cerr;
using std::endl;

static const std::string ZEROS(1024, '\0');

static void secureDelete(const char * filename) {
    // Wipe a file
    File file(filename, O_RDWR);
    size_t length=file.seek(0, SEEK_END);
    file.seek(0);
    while (length) {
        size_t block=std::min(length, ZEROS.length());
        file.write(&ZEROS[0], block);
        length-=block;
    }
    unlink(filename);
    
    // Check if there are any hard links
    struct stat statbuf;
    file.stat(&statbuf);
    if (statbuf.st_nlink)
        cerr << filename << ": warning: there are other links to this file" << endl;
}

int main(int argc, char ** argv) {
    setlocale(LC_ALL, "");
    for (int i=1; i<argc; i++) {
        const char * filename=argv[i];
        try {
            secureDelete(filename);
        }
        catch (const std::system_error &e) {
            cerr << filename << ": error: " << e.what() << endl;
        }
    }
    return 0;
}
