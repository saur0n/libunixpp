/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  File operations
 *  
 *  © 2019—2021, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNIXPP_FILE_HPP
#define __UNIXPP_FILE_HPP

#include <fcntl.h>
#include <sys/file.h>
#include "Stream.hpp"

namespace upp {

class File : public Stream {
    friend class Directory;
public:
    /** **/
    const int REMOVEDIR=AT_REMOVEDIR;
    /** Open file for reading **/
    File(const char * filename);
    /** Open and possibly create a file **/
    File(const char * filename, int flags, int mode=0600);
    /** Open file for reading relative to this directory **/
    File(const File &dir, const char * filename);
    /** Open file for reading relative to this directory **/
    File(const File &dir, const char * filename, int flags);
    /** Set an extended attribute value **/
    void setAttribute(const char * name, const char * value, size_t size, int flags=0);
    /** Retrieve an extended attribute value **/
    size_t getAttribute(const char * name, char * value, size_t size);
    /** List extended attribute names **/
    void listAttributes(char * list, size_t size);
    /** Remove an extended attribute **/
    void removeAttribute(const char * name);
    /** Get filesystem statistics **/
    void statfs(struct statfs * buf);
    /** Truncate a file to a specified length **/
    void truncate(off_t length=0);
    /** Manipulate file space **/
    void allocate(int mode, off_t offset, off_t len);
    /** Change working directory to this directory **/
    void chdir();
    /** Apply or remove an advisory lock on an open file **/
    void lock(int operation);
    /** Create a special file relative to this directory **/
    void mknod(const char * pathname, mode_t mode, dev_t device);
    /** Make directory relative to this directory **/
    void mkdir(const char * pathname, mode_t mode);
    /** Delete a file relative to this directory **/
    void unlink(const char * pathname, int flags=0);
    /** Make a new name for a file relative to this directory **/
    void symlink(const char * target, const char * linkpath);
    /** Make a new name for a file relative to this directory **/
    void link(const char * oldpath, const char * newpath, int flags=0);
    /** Change the name/location of a file relative to this directory **/
    void rename(const char * oldpath, const char * newpath);
#ifndef PLATFORM_MUSL
    /** Change the name/location of a file relative to this directory **/
    void rename(const char * oldpath, const char * newpath, int flags);
#endif
    /** Check user's permissions for a file relative to this directory **/
    bool access(const char * pathname, int mode, int flags=0);
    /** Change permissions of a file **/
    void chmod(mode_t mode);
    /** Change permissions of a file relative to this directory **/
    void chmod(const char * pathname, mode_t mode, int flags=0);
    /** Change ownership of a file **/
    void chown(uid_t owner, gid_t group);
    /** Change ownership of a file relative to this directory **/
    void chown(const char * pathname, uid_t owner, gid_t group, int flags=0);
    /** Read value of a symbolic link relative to this directory **/
    size_t readlink(const char * pathname, char * buffer, size_t length);
    /** Get file status **/
    void stat(struct stat * statbuf);
    /** Get file status relative to this directory **/
    void stat(const char * pathname, struct stat * statbuf, int flags=0);
    /** Synchronize a file's in-core state with storage device **/
    void sync();
    /** Synchronize a file's in-core state with storage device **/
    void syncData();
    /** Sync a file segment with disk **/
    void sync(off64_t offset, off64_t nbytes, unsigned int flags=0);
    /** Initiate file readahead into page cache **/
    void readAhead(off64_t offset, size_t count);
    /** Commit filesystem caches to disk **/
    void syncFileSystem();
    /** Change file timestamps **/
    void utime(const struct timespec times[2]);
    /** Change file timestamps relative to this directory **/
    void utime(const char * pathname, const struct timespec times[2], int flags=0);
    /** **/
    void exec(const char * pathname, char ** const argv, char ** const envp, int flags=0);
#ifndef PLATFORM_MUSL
    /** Get file status (extended) relative to this directory **/
    void stat(const char * pathname, unsigned int mask, struct statx * statxbuf, int flags=0);
#endif
    /** Set file mode creation mask **/
    static mode_t umask(mode_t mask);
};

}

#endif
