/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Directory operations
 *  
 *  © 2019—2020, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNIXPP_DIRECTORY_HPP
#define __UNIXPP_DIRECTORY_HPP

#include <sys/types.h>
#include <dirent.h>

namespace nx {

class File;

/**/
class Directory {
public:
    /**/
    typedef struct dirent Entry;
    /** Open a directory stream **/
    explicit Directory(const char * directory);
    /** Open a directory based on file opened with O_DIRECTORY flag **/
    explicit Directory(File &file);
    /** Close the directory stream **/
    ~Directory();
    /** Read a directory entry from the directory **/
    Entry * read();
    /** Rewind to the beginning of the directory **/
    void rewind();
    /** Returns current location in the directory stream **/
    long tell();
    /** Seek to the given position on a directory **/
    void seek(long position);
    
private:
    Directory(DIR * dirp);
    Directory(const Directory &other)=delete;
    Directory &operator =(const Directory &other)=delete;
    
    DIR * dirp;
};

}

#endif
