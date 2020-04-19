/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  ...
 *  
 *  © 2019—2020, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include "exception.hppi"
#include "Stream.hpp"

using namespace nx;

Stream::Stream(const Stream &other) : fd(dup(other.fd)) {
    THROW_SYSTEM_ERROR_IF(fd<0);
}

Stream::Stream(const Stream &other, int newfd) :
        Stream(dup2(other.fd, newfd)) {}

Stream::Stream(const Stream &other, int newfd, int flags) :
        Stream(dup3(other.fd, newfd, flags)) {}

Stream::~Stream() {
    close(fd);
}

off_t Stream::seek(off_t offset, int whence) {
    off_t result=::lseek(fd, offset, whence);
    THROW_SYSTEM_ERROR_IF(result<0);
    return result;
}

size_t Stream::read(void * buffer, size_t count) {
    ssize_t result=::read(fd, buffer, count);
    THROW_SYSTEM_ERROR_IF(result<0);
    return size_t(result);
}

size_t Stream::read(void * buffer, size_t count, off_t offset) {
    ssize_t result=::pread(fd, buffer, count, offset);
    THROW_SYSTEM_ERROR_IF(result<0);
    return size_t(result);
}

size_t Stream::write(const void * buffer, size_t count) {
    ssize_t result=::write(fd, buffer, count);
    THROW_SYSTEM_ERROR_IF(result<0);
    return size_t(result);
}

size_t Stream::write(const void * buffer, size_t count, off_t offset) {
    ssize_t result=::pwrite(fd, buffer, count, offset);
    THROW_SYSTEM_ERROR_IF(result<0);
    return size_t(result);
}

void Stream::stat(struct stat * statbuf) {
    int result=fstat(fd, statbuf);
    THROW_SYSTEM_ERROR_IF(result<0);
}

unsigned Stream::getFlags() {
    return fcntl(F_GETFD);
}

void Stream::setFlags(unsigned flags) {
    fcntl(F_SETFD, flags);
}

unsigned Stream::getStatusFlags() {
    return fcntl(F_GETFL);
}

void Stream::setStatusFlags(unsigned flags) {
    fcntl(F_SETFL, flags);
}

int Stream::getOwner() {
    return fcntl(fd, F_GETOWN);
}

size_t Stream::sendfile(Stream &from, size_t count) {
    ssize_t result=::sendfile(fd, from.fd, nullptr, count);
    THROW_SYSTEM_ERROR_IF(result<0);
    return size_t(result);
}

size_t Stream::sendfile(Stream &from, off_t &offset, size_t count) {
    ssize_t result=::sendfile(fd, from.fd, &offset, count);
    THROW_SYSTEM_ERROR_IF(result<0);
    return size_t(result);
}

Stream::Stream(int fd) : fd(fd) {
    THROW_SYSTEM_ERROR_IF(fd<0);
}

unsigned Stream::ioctl(int request, void * argp) {
    int result=::ioctl(fd, request, argp);
    THROW_SYSTEM_ERROR_IF(result<0);
    return unsigned(result);
}

unsigned Stream::fcntl(int cmd) {
    int result=::fcntl(fd, cmd);
    THROW_SYSTEM_ERROR_IF(result<0);
    return unsigned(result);
}

unsigned Stream::fcntl(int cmd, int arg) {
    int result=::fcntl(fd, cmd, arg);
    THROW_SYSTEM_ERROR_IF(result<0);
    return unsigned(result);
}
