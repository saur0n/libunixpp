#include <sys/ioctl.h>
#include <sys/stat.h>
#include "exception.hppi"
#include "Stream.hpp"

using namespace nx;

Stream::Stream(const Stream &other) : fd(dup(other.fd)) {
    THROW_SYSTEM_ERROR_IF(fd<0);
}

Stream::Stream(const Stream &other, int newfd) : fd(dup2(other.fd, newfd)) {
    THROW_SYSTEM_ERROR_IF(fd<0);
}

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
    THROW_NOT_IMPLEMENTED;
}

void Stream::setFlags(unsigned flags) {
    THROW_NOT_IMPLEMENTED;
}

Stream::Stream(int fd) : fd(fd) {
    THROW_SYSTEM_ERROR_IF(fd<0);
}

unsigned Stream::ioctl(int request, void * argp) {
    int result=::ioctl(fd, request, argp);
    THROW_SYSTEM_ERROR_IF(result<0);
    return unsigned(result);
}
