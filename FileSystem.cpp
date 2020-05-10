/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Static filesystem operations
 *  
 *  © 2019—2020, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include <linux/limits.h>
#include "exception.hppi"
#include "FileSystem.hpp"

using namespace nx;
using std::string;

bool FileSystem::access(const char * pathname, int mode) {
    int retval=::access(pathname, mode);
    if (retval<0) {
        if ((mode==F_OK)&&(errno==ENOENT))
            return false;
        else if (errno==EACCES)
            return false;
        else
            THROW_SYSTEM_ERROR;
    }
    else
        return true;
}

void FileSystem::chdir(const char * path) {
    NORMAL_OP_WRAPPER(::chdir(path));
}

void FileSystem::chmod(const char * pathname, mode_t mode) {
    NORMAL_OP_WRAPPER(::chmod(pathname, mode));
}

void FileSystem::chown(const char * pathname, uid_t owner, gid_t group) {
    NORMAL_OP_WRAPPER(::chown(pathname, owner, group));
}

string FileSystem::getcwd() {
    char buffer[PATH_MAX];
    NORMAL_POP_WRAPPER(::getcwd(buffer, sizeof(buffer)));
    return buffer;
}

void FileSystem::lchown(const char * pathname, uid_t owner, gid_t group) {
    NORMAL_OP_WRAPPER(::lchown(pathname, owner, group));
}

void FileSystem::link(const char * oldpath, const char * newpath) {
    NORMAL_OP_WRAPPER(::link(oldpath, newpath));
}

int FileSystem::lstat(const char * pathname, struct stat * statbuf) {
    THROW_NOT_IMPLEMENTED;
}

int FileSystem::mkdir(const char * pathname, mode_t mode) {
    THROW_NOT_IMPLEMENTED;
}

ssize_t readlink(const char * pathname, char * buf, size_t bufsiz) {
    THROW_NOT_IMPLEMENTED;
}

int FileSystem::rename(const char * oldpath, const char * newpath) {
    THROW_NOT_IMPLEMENTED;
}

int FileSystem::rmdir(const char * pathname) {
    THROW_NOT_IMPLEMENTED;
}

int FileSystem::stat(const char * pathname, struct stat * statbuf) {
    THROW_NOT_IMPLEMENTED;
}

int FileSystem::statfs(const char * path, struct statfs * buf) {
    THROW_NOT_IMPLEMENTED;
}

void FileSystem::symlink(const char * target, const char * linkpath) {
    NORMAL_OP_WRAPPER(::symlink(target, linkpath));
}

void FileSystem::sync() {
    ::sync();
}

void FileSystem::truncate(const char * pathname, off_t length) {
    NORMAL_OP_WRAPPER(::truncate(pathname, length));
}

void FileSystem::unlink(const char * pathname) {
    NORMAL_OP_WRAPPER(::unlink(pathname))
}

int FileSystem::utimes(const char * filename, const struct timeval times[2]) {
    THROW_NOT_IMPLEMENTED;
}

void FileSystem::setAttribute(const char * pathname, const char * name, const char * value, size_t size, int flags) {
    THROW_NOT_IMPLEMENTED;
}

size_t FileSystem::getAttribute(const char * pathname, const char * name, char * value, size_t size) {
    THROW_NOT_IMPLEMENTED;
}

void FileSystem::listAttributes(const char * pathname, char * list, size_t size) {
    THROW_NOT_IMPLEMENTED;
}

void FileSystem::removeAttribute(const char * pathname, const char * name) {
    THROW_NOT_IMPLEMENTED;
}
