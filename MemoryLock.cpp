/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Memory locking operations
 *  
 *  © 2019—2021, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include "exception.hppi"
#include "MemoryLock.hpp"

using namespace upp;

MemoryLock::MemoryLock(void * addr, size_t length) : MemoryRegion(addr, length) {
    NORMAL_OP_WRAPPER(mlock(addr, length));
}

MemoryLock::MemoryLock(void * addr, size_t length, int flags) : MemoryRegion(addr, length) {
    NORMAL_OP_WRAPPER(mlock2(addr, length, flags));
}

MemoryLock::~MemoryLock() {
    munlock(getAddress(), getLength());
}

void MemoryLock::lockAll(int flags) {
    NORMAL_OP_WRAPPER(mlockall(flags));
}

void MemoryLock::unlockAll() {
    NORMAL_OP_WRAPPER(munlockall());
}
