/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Static filesystem operations
 *  
 *  © 2019—2020, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include "exception.hppi"
#include "FileSystem.hpp"

using namespace nx::FileSystem;

int access(const char * pathname, int mode) {
    THROW_NOT_IMPLEMENTED;
}

int chdir(const char * path) {
    THROW_NOT_IMPLEMENTED;
}

int chmod(const char * pathname, mode_t mode) {
    THROW_NOT_IMPLEMENTED;
}

int chown(const char * pathname, uid_t owner, gid_t group) {
    THROW_NOT_IMPLEMENTED;
}

char * getcwd(char * buf, size_t size) {
    THROW_NOT_IMPLEMENTED;
}

int lchown(const char * pathname, uid_t owner, gid_t group) {
    THROW_NOT_IMPLEMENTED;
}

int link(const char * oldpath, const char * newpath) {
    THROW_NOT_IMPLEMENTED;
}

int lstat(const char * pathname, struct stat * statbuf) {
    THROW_NOT_IMPLEMENTED;
}

int mkdir(const char * pathname, mode_t mode) {
    THROW_NOT_IMPLEMENTED;
}

ssize_t readlink(const char * pathname, char * buf, size_t bufsiz) {
    THROW_NOT_IMPLEMENTED;
}

int rename(const char * oldpath, const char * newpath) {
    THROW_NOT_IMPLEMENTED;
}

int rmdir(const char * pathname) {
    THROW_NOT_IMPLEMENTED;
}

int stat(const char * pathname, struct stat * statbuf) {
    THROW_NOT_IMPLEMENTED;
}

int statfs(const char * path, struct statfs * buf) {
    THROW_NOT_IMPLEMENTED;
}

int symlink(const char * target, const char * linkpath) {
    THROW_NOT_IMPLEMENTED;
}

void sync() {
    THROW_NOT_IMPLEMENTED;
}

int truncate(const char * pathname, off_t length) {
    THROW_NOT_IMPLEMENTED;
}

int unlink(const char * pathname) {
    THROW_NOT_IMPLEMENTED;
}

int utimes(const char * filename, const struct timeval times[2]) {
    THROW_NOT_IMPLEMENTED;
}

void setAttribute(const char * pathname, const char * name, const char * value, size_t size, int flags) {
    THROW_NOT_IMPLEMENTED;
}

size_t getAttribute(const char * pathname, const char * name, char * value, size_t size) {
    THROW_NOT_IMPLEMENTED;
}

void listAttributes(const char * pathname, char * list, size_t size) {
    THROW_NOT_IMPLEMENTED;
}

void removeAttribute(const char * pathname, const char * name) {
    THROW_NOT_IMPLEMENTED;
}
