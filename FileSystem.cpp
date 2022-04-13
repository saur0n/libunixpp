/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Static filesystem operations
 *  
 *  © 2019—2022, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include <linux/limits.h>
#include <sys/time.h>
#include <sys/xattr.h>
#include "exception.hppi"
#include "FileSystem.hpp"

using namespace upp;
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

void FileSystem::chroot(const char * path) {
    NORMAL_OP_WRAPPER(::chroot(path));
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

void FileSystem::lstat(const char * pathname, struct stat * statbuf) {
    NORMAL_OP_WRAPPER(::lstat(pathname, statbuf))
}

struct stat FileSystem::lstat(const char * pathname) {
    struct stat statbuf;
    FileSystem::lstat(pathname, &statbuf);
    return statbuf;
}

void FileSystem::mkdir(const char * pathname, mode_t mode) {
    NORMAL_OP_WRAPPER(::mkdir(pathname, mode))
}

void FileSystem::mknod(const char * pathname, mode_t mode, dev_t dev) {
    NORMAL_OP_WRAPPER(::mknod(pathname, mode, dev));
}

ssize_t FileSystem::readlink(const char * pathname, char * buf, size_t bufsiz) {
    THROW_NOT_IMPLEMENTED;
}

void FileSystem::rename(const char * oldpath, const char * newpath) {
    NORMAL_OP_WRAPPER(::rename(oldpath, newpath))
}

void FileSystem::rmdir(const char * pathname) {
    NORMAL_OP_WRAPPER(::rmdir(pathname))
}

void FileSystem::stat(const char * pathname, struct stat * statbuf) {
    NORMAL_OP_WRAPPER(::stat(pathname, statbuf))
}

struct stat FileSystem::stat(const char * pathname) {
    struct stat statbuf;
    FileSystem::stat(pathname, &statbuf);
    return statbuf;
}

void FileSystem::statfs(const char * path, Statistics &buf) {
    NORMAL_OP_WRAPPER(::statfs(path, &buf));
}

FileSystem::Statistics FileSystem::statfs(const char * path) {
    struct statfs result;
    FileSystem::statfs(path, result);
    return result;
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

void FileSystem::utimes(const char * filename, const struct timeval times[2]) {
    NORMAL_OP_WRAPPER(::utimes(filename, times));
}

void FileSystem::setAttribute(const char * pathname, const char * name, const char * value, size_t size, int flags) {
    THROW_SYSTEM_ERROR_STD(setxattr(pathname, name, value, size, flags));
}

void FileSystem::setAttributeL(const char * pathname, const char * name, const char * value, size_t size, int flags) {
    THROW_SYSTEM_ERROR_STD(lsetxattr(pathname, name, value, size, flags));
}

size_t FileSystem::getAttribute(const char * pathname, const char * name, char * value, size_t size) {
    ssize_t retval=getxattr(pathname, name, value, size);
    THROW_SYSTEM_ERROR_IF(retval<0);
    return size_t(retval);
}

size_t FileSystem::getAttributeL(const char * pathname, const char * name, char * value, size_t size) {
    ssize_t retval=lgetxattr(pathname, name, value, size);
    THROW_SYSTEM_ERROR_IF(retval<0);
    return size_t(retval);
}

size_t FileSystem::listAttributes(const char * pathname, char * list, size_t size) {
    ssize_t retval=listxattr(pathname, list, size);
    THROW_SYSTEM_ERROR_IF(retval<0);
    return size_t(retval);
}

size_t FileSystem::listAttributesL(const char * pathname, char * list, size_t size) {
    ssize_t retval=llistxattr(pathname, list, size);
    THROW_SYSTEM_ERROR_IF(retval<0);
    return size_t(retval);
}

void FileSystem::removeAttribute(const char * pathname, const char * name) {
    THROW_SYSTEM_ERROR_STD(removexattr(pathname, name));
}

void FileSystem::removeAttributeL(const char * pathname, const char * name) {
    THROW_SYSTEM_ERROR_STD(lremovexattr(pathname, name));
}
