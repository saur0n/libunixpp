/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Unit tests
 *  
 *  © 2023, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include "unittest.hpp"
#include "../Directory.hpp"

static void run() {
    // Prepare a directory for tests
    FileSystem::mkdirp("/tmp/upp-test");
    FileSystem::mkdirp("/tmp/upp-test/alpha");
    FileSystem::mkdirp("/tmp/upp-test/beta");
    
    // Scan the directory
    Directory directory("/tmp/upp-test");
    std::vector<std::string> names;
    while (const Directory::Entry * e=directory.read())
        names.push_back(e->d_name);
    assert(find(names.begin(), names.end(), "alpha")!=names.end());
    assert(find(names.begin(), names.end(), "beta")!=names.end());
    
    // Get the directory list
    DirectoryList dlist("/tmp/upp-test", nullptr, alphasort);
    assert(dlist.length()==4);
    assert(0==strcmp(dlist[0].d_name, "."));
    assert(0==strcmp(dlist[1].d_name, ".."));
    assert(0==strcmp(dlist[2].d_name, "alpha"));
    assert(0==strcmp(dlist[3].d_name, "beta"));
}

REGISTER("Directory", run);
