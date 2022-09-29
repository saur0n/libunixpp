/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Static filesystem operations
 *  
 *  © 2019—2022, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNIXPP_FILESYSTEM_HPP
#define __UNIXPP_FILESYSTEM_HPP

#include <string>
#include <sys/stat.h>
#include <sys/vfs.h>
#include <unistd.h>

namespace upp {

namespace FileSystem {
    /** Filesystem statistics **/
    typedef struct ::statfs Statistics;
    /** Check user's permissions for a file **/
    bool access(const char * pathname, int mode=F_OK);
    /** Change working directory **/
    void chdir(const char * path);
    /** Change permissions of a file **/
    void chmod(const char * pathname, mode_t mode);
    /** Change ownership of a file **/
    void chown(const char * pathname, uid_t owner, gid_t group);
    /** Change root directory **/
    void chroot(const char * path);
    /** Get current working directory **/
    std::string getcwd();
    /** Change ownership of a file, do not follow symlinks **/
    void lchown(const char * pathname, uid_t owner, gid_t group);
    /** Make a new name for a file **/
    void link(const char * oldpath, const char * newpath);
    /** Get file status, do not follow symlinks **/
    void lstat(const char * pathname, struct stat * statbuf);
    /** Get file status, do not follow symlinks **/
    struct stat lstat(const char * pathname);
    /** Create a directory **/
    void mkdir(const char * pathname, mode_t mode=0700);
    /** Create a special or ordinary file **/
    void mknod(const char * pathname, mode_t mode, dev_t dev);
    /** Read value of a symbolic link **/
    ssize_t readlink(const char * pathname, char * buf, size_t bufsiz);
    /** Change the name or location of a file **/
    void rename(const char * oldpath, const char * newpath);
    /** Delete a directory **/
    void rmdir(const char * pathname);
    /** Get file status **/
    void stat(const char * pathname, struct stat * statbuf);
    /** Get file status **/
    struct stat stat(const char * pathname);
    /** Get filesystem statistics **/
    void statfs(const char * path, Statistics &buf);
    /** Get filesystem statistics **/
    Statistics statfs(const char * path);
    /** Make a new name for a file **/
    void symlink(const char * target, const char * linkpath);
    /** Synchronize cached writes to persistent storage **/
    void sync();
    /** Truncate a file to a specified length **/
    void truncate(const char * pathname, off_t length=0);
    /** Delete a name and possibly the file it refers to **/
    void unlink(const char * pathname);
    /** Change file last access and modification times **/
    void utimes(const char * filename, const struct timeval times[2]);
    /** Set an extended attribute value **/
    void setAttribute(const char * pathname, const char * name, const char * value, size_t size, int flags=0);
    /** Set an extended attribute value, do not follow symbolic links **/
    void setAttributeL(const char * pathname, const char * name, const char * value, size_t size, int flags=0);
    /** Retrieve an extended attribute value **/
    size_t getAttribute(const char * pathname, const char * name, char * value, size_t size);
    /** Retrieve an extended attribute value, do not follow symbolic links **/
    size_t getAttributeL(const char * pathname, const char * name, char * value, size_t size);
    /** List extended attribute names **/
    size_t listAttributes(const char * pathname, char * list, size_t size);
    /** List extended attribute names, do not follow symbolic links **/
    size_t listAttributesL(const char * pathname, char * list, size_t size);
    /** Remove an extended attribute **/
    void removeAttribute(const char * pathname, const char * name);
    /** Remove an extended attribute, do not follow symbolic links **/
    void removeAttributeL(const char * pathname, const char * name);
}

}

#endif
