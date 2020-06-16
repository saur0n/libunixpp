/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Memory operations
 *  
 *  © 2019—2020, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include <sys/mman.h>
#include "exception.hppi"
#include "MemoryRegion.hpp"

using namespace nx;

MemoryRegion::MemoryRegion(void * address, size_t length) :
        address(address), length(length) {}

void MemoryRegion::incore(unsigned char * result) {
    NORMAL_OP_WRAPPER(mincore(address, length, result));
}

void MemoryRegion::protect(int prot) {
    NORMAL_OP_WRAPPER(mprotect(address, length, prot));
}
