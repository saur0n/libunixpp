/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  File operations
 *  
 *  © 2019—2024, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include <sys/stat.h>
#include <sys/vfs.h>
#include <sys/xattr.h>
#include "exception.hppi"
#include "File.hpp"

using namespace upp;

/******************************************************************************/

File::File(const char * filename) : Stream(open(filename, O_RDONLY)) {}

File::File(const char * filename, int flags, int mode) : Stream(open(filename, flags, mode)) {}

File::File(const File &dir, const char * filename) : Stream(openat(dir.getDescriptor(), filename, O_RDONLY)) {}

File::File(const File &dir, const char * filename, int flags) : Stream(openat(dir.getDescriptor(), filename, flags)) {}

void File::setAttribute(const char * name, const char * value, size_t size, int flags) {
    THROW_SYSTEM_ERROR_STD(fsetxattr(getDescriptor(), name, value, size, flags));
}

size_t File::getAttribute(const char * name, char * value, size_t size) {
    ssize_t retval=fgetxattr(getDescriptor(), name, value, size);
    THROW_SYSTEM_ERROR_IF(retval<0);
    return size_t(retval);
}

void File::listAttributes(char * list, size_t size) {
    THROW_SYSTEM_ERROR_STD(flistxattr(getDescriptor(), list, size));
}

void File::removeAttribute(const char * name) {
    THROW_SYSTEM_ERROR_STD(fremovexattr(getDescriptor(), name));
}

void File::statfs(struct statfs &buf) {
    THROW_SYSTEM_ERROR_STD(fstatfs(getDescriptor(), &buf));
}

void File::truncate(off_t length) {
    THROW_SYSTEM_ERROR_STD(ftruncate(getDescriptor(), length));
}

void File::allocate(int mode, off_t offset, off_t len) {
    THROW_SYSTEM_ERROR_STD(fallocate(getDescriptor(), mode, offset, len));
}

void File::chdir() {
    THROW_SYSTEM_ERROR_STD(fchdir(getDescriptor()));
}

void File::lock(int operation) {
    THROW_SYSTEM_ERROR_STD(flock(getDescriptor(), operation));
}

void File::lock(int cmd, off_t len) {
    THROW_SYSTEM_ERROR_STD(lockf(getDescriptor(), cmd, len));
}

void File::mknod(const char * pathname, mode_t mode, dev_t device) {
    THROW_SYSTEM_ERROR_STD(mknodat(getDescriptor(), pathname, mode, device));
}

void File::mkdir(const char * pathname, mode_t mode) {
    THROW_SYSTEM_ERROR_STD(mkdirat(getDescriptor(), pathname, mode));
}

void File::unlink(const char * pathname, int flags) {
    THROW_SYSTEM_ERROR_STD(unlinkat(getDescriptor(), pathname, flags));
}

void File::symlink(const char * target, const char * linkpath) {
    THROW_SYSTEM_ERROR_STD(symlinkat(target, getDescriptor(), linkpath));
}

void File::link(const char * oldpath, const char * newpath, int flags) {
    int fd=getDescriptor();
    THROW_SYSTEM_ERROR_STD(linkat(fd, oldpath, fd, newpath, flags));
}

void File::rename(const char * oldpath, const char * newpath) {
    int fd=getDescriptor();
    THROW_SYSTEM_ERROR_STD(renameat(fd, oldpath, fd, newpath));
}

#ifndef PLATFORM_MUSL
void File::rename(const char * oldpath, const char * newpath, int flags) {
    THROW_SYSTEM_ERROR_STD(renameat2(getDescriptor(), oldpath, getDescriptor(), newpath, flags));
}
#endif

bool File::access(const char * pathname, int mode, int flags) {
    return F_OK==faccessat(getDescriptor(), pathname, mode, flags);
}

void File::chmod(mode_t mode) {
    THROW_SYSTEM_ERROR_STD(fchmod(getDescriptor(), mode));
}

void File::chmod(const char * pathname, mode_t mode, int flags) {
    THROW_SYSTEM_ERROR_STD(fchmodat(getDescriptor(), pathname, mode, flags));
}

void File::chown(uid_t owner, gid_t group) {
    THROW_SYSTEM_ERROR_STD(fchown(getDescriptor(), owner, group));
}

void File::chown(const char * pathname, uid_t owner, gid_t group, int flags) {
    THROW_SYSTEM_ERROR_STD(fchownat(getDescriptor(), pathname, owner, group, flags));
}

size_t File::readlink(const char * pathname, char * buffer, size_t length) {
    ssize_t retval=readlinkat(getDescriptor(), pathname, buffer, length);
    THROW_SYSTEM_ERROR_IF(retval<0);
    return size_t(retval);
}

void File::stat(struct stat &statbuf) {
    THROW_SYSTEM_ERROR_STD(fstat(getDescriptor(), &statbuf));
}

void File::stat(const char * pathname, struct stat &statbuf, int flags) {
    THROW_SYSTEM_ERROR_STD(fstatat(getDescriptor(), pathname, &statbuf, flags));
}

void File::sync() {
    THROW_SYSTEM_ERROR_STD(fsync(getDescriptor()));
}

void File::syncData() {
    THROW_SYSTEM_ERROR_STD(fdatasync(getDescriptor()));
}

void File::sync(Offset offset, Offset nbytes, unsigned int flags) {
    THROW_SYSTEM_ERROR_STD(sync_file_range(getDescriptor(), offset, nbytes, flags));
}

void File::readAhead(Offset offset, size_t count) {
    THROW_SYSTEM_ERROR_STD(readahead(getDescriptor(), offset, count));
}

void File::syncFileSystem() {
    THROW_SYSTEM_ERROR_STD(syncfs(getDescriptor()));
}

void File::utime(const struct timespec times[2]) {
    THROW_SYSTEM_ERROR_STD(futimens(getDescriptor(), times));
}

void File::utime(const char * pathname, const struct timespec times[2], int flags) {
    THROW_SYSTEM_ERROR_STD(utimensat(getDescriptor(), pathname, times, flags));
}

void File::exec(const char * pathname, char ** const argv, char ** const envp, int flags) {
    
}

#ifndef PLATFORM_MUSL
void File::stat(const char * pathname, unsigned int mask, struct statx &statxbuf, int flags) {
    THROW_SYSTEM_ERROR_STD(statx(getDescriptor(), pathname, flags, mask, &statxbuf));
}
#endif

mode_t File::umask(mode_t mask) {
    return ::umask(mask);
}

static size_t copyFileRange(int in, off_t * offIn, int out, off_t * offOut, size_t length, unsigned flags) {
    ssize_t result=copy_file_range(in, offIn, out, offOut, length, flags);
    THROW_SYSTEM_ERROR_IF(result<0);
    return size_t(result);
}

size_t File::copyRange(File &out, size_t length, unsigned flags) {
    return copyFileRange(getDescriptor(), nullptr, out.getDescriptor(), nullptr, length, flags);
}

size_t File::copyRange(File &out, off_t &offOut, size_t length, unsigned flags) {
    return copyFileRange(getDescriptor(), nullptr, out.getDescriptor(), &offOut, length, flags);
}

size_t File::copyRange(off_t &offIn, File &out, size_t length, unsigned flags) {
    return copyFileRange(getDescriptor(), &offIn, out.getDescriptor(), nullptr, length, flags);
}

size_t File::copyRange(off_t &offIn, File &out, off_t &offOut, size_t length, unsigned flags) {
    return copyFileRange(getDescriptor(), &offIn, out.getDescriptor(), &offOut, length, flags);
}

