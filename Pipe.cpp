/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Pipe operations
 *  
 *  © 2019—2021, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include <fcntl.h>
#include "exception.hppi"
#include "Pipe.hpp"

using namespace upp;
using std::pair;

pair<Pipe, Pipe> Pipe::create() {
    int pipefd[2];
    THROW_SYSTEM_ERROR_STD(pipe(pipefd));
    return pair<Pipe, Pipe>(pipefd[0], pipefd[1]);
}

pair<Pipe, Pipe> Pipe::create(int flags) {
    int pipefd[2];
    THROW_SYSTEM_ERROR_STD(pipe2(pipefd, flags));
    return pair<Pipe, Pipe>(pipefd[0], pipefd[1]);
}

size_t Pipe::tee(Pipe &out, size_t length, unsigned int flags) {
    ssize_t result=::tee(getDescriptor(), out.getDescriptor(), length, flags);
    THROW_SYSTEM_ERROR_IF(result<0);
    return size_t(result);
}

unsigned Pipe::getCapacity() {
    return fcntl(F_GETPIPE_SZ);
}

void Pipe::setCapacity(unsigned capacity) {
    fcntl(F_SETPIPE_SZ, capacity);
}

Pipe::Pipe(int fd) : Stream(fd) {}
