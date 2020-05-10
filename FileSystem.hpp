/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Static filesystem operations
 *  
 *  © 2019—2020, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNIXPP_FILESYSTEM_HPP
#define __UNIXPP_FILESYSTEM_HPP

#include <string>
#include <sys/stat.h>
#include <unistd.h>

namespace nx {

namespace FileSystem {
    /** Check user's permissions for a file **/
    bool access(const char * pathname, int mode=F_OK);
    /** Change working directory **/
    void chdir(const char * path);
    /** Change permissions of a file **/
    void chmod(const char * pathname, mode_t mode);
    /** Change ownership of a file **/
    void chown(const char * pathname, uid_t owner, gid_t group);
    /** Get current working directory **/
    std::string getcwd();
    /** Change ownership of a file, do not follow symlinks **/
    void lchown(const char * pathname, uid_t owner, gid_t group);
    /** Make a new name for a file **/
    void link(const char * oldpath, const char * newpath);
    /**/
    int lstat(const char * pathname, struct stat * statbuf);
    /** Create a directory **/
    void mkdir(const char * pathname, mode_t mode=0700);
    /**/
    ssize_t readlink(const char * pathname, char * buf, size_t bufsiz);
    /**/
    int rename(const char * oldpath, const char * newpath);
    /**/
    int rmdir(const char * pathname);
    /**/
    int stat(const char * pathname, struct stat * statbuf);
    /**/
    int statfs(const char * path, struct statfs * buf);
    /** Make a new name for a file **/
    void symlink(const char * target, const char * linkpath);
    /**/
    void sync();
    /** Truncate a file to a specified length **/
    void truncate(const char * pathname, off_t length);
    /** Delete a name and possibly the file it refers to **/
    void unlink(const char * pathname);
    /**/
    int utimes(const char * filename, const struct timeval times[2]);
    /** Set an extended attribute value **/
    void setAttribute(const char * pathname, const char * name, const char * value, size_t size, int flags=0);
    /** Retrieve an extended attribute value **/
    size_t getAttribute(const char * pathname, const char * name, char * value, size_t size);
    /** List extended attribute names **/
    void listAttributes(const char * pathname, char * list, size_t size);
    /** Remove an extended attribute **/
    void removeAttribute(const char * pathname, const char * name);
}

}

#endif
