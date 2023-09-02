/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Directory operations
 *  
 *  © 2019—2023, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNIXPP_DIRECTORY_HPP
#define __UNIXPP_DIRECTORY_HPP

#include <sys/types.h>
#include <dirent.h>

namespace upp {

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

/** List of files in the directory **/
class DirectoryList {
public:
    /** Filter function **/
    using Filter=int(const Directory::Entry *);
    /** Comparison function **/
    using Compare=int(const Directory::Entry **, const Directory::Entry **);
    /** Scan a directory for matching entries **/
    DirectoryList(const char * name, Filter filter=nullptr, Compare compare=nullptr);
    /** Free the directory list **/
    ~DirectoryList();
    /** Returns the length of the list **/
    unsigned length() const { return count; }
    /** Returns the i-th directory entry **/
    const Directory::Entry &operator [](unsigned index) const { return *namelist[index]; }
    
private:
    explicit DirectoryList(const DirectoryList &other)=delete;
    DirectoryList &operator =(const DirectoryList &other)=delete;
    
    unsigned count;
    Directory::Entry ** namelist;
};

}

#endif
