/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Directory operations
 *  
 *  © 2019—2023, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include "Directory.hpp"
#include "File.hpp"
#include "exception.hppi"

using namespace upp;

/******************************************************************************/

Directory::Directory(const char * directory) : Directory(opendir(directory)) {}

Directory::Directory(File &file) : Directory(fdopendir(file.getDescriptor())) {}

Directory::~Directory() {
    closedir(dirp);
}

Directory::Entry * Directory::read() {
    errno=0;
    auto retval=readdir(dirp);
    THROW_SYSTEM_ERROR_IF((retval==nullptr)&&(errno!=0));
    return retval;
}

void Directory::rewind() {
    rewinddir(dirp);
}

long Directory::tell() {
    NORMAL_IO_WRAPPER(long, long, telldir(dirp));
}

void Directory::seek(long position) {
    seekdir(dirp, position);
}

Directory::Directory(DIR * dirp) : dirp(dirp) {
    THROW_SYSTEM_ERROR_IF(dirp==nullptr);
}

/******************************************************************************/

DirectoryList::DirectoryList(const char * name, Filter filter, Compare compare) {
    int retval=::scandir(name, &namelist, filter, compare);
    THROW_SYSTEM_ERROR_IF(retval<0);
    count=unsigned(retval);
}

DirectoryList::~DirectoryList() {
    for (unsigned i=0; i<count; i++)
        ::free(namelist[i]);
    ::free(namelist);
}
