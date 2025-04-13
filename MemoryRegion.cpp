/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Memory operations
 *  
 *  © 2019—2025, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include <sys/mman.h>
#include "exception.hppi"
#include "MemoryRegion.hpp"

using namespace upp;

/******************************************************************************/

ProtectionKey::ProtectionKey(unsigned int accessRights) :
        pkey(pkey_alloc(0, accessRights)) {}

ProtectionKey::ProtectionKey(unsigned int flags, unsigned int accessRights) :
        pkey(pkey_alloc(flags, accessRights)) {}

ProtectionKey::~ProtectionKey() {
    pkey_free(pkey);
}

MemoryRegion::MemoryRegion(void * address, size_t length) :
        address(address), length(length) {}

void MemoryRegion::advise(int advise) {
    NORMAL_OP_WRAPPER(madvise(address, length, advise));
}

void MemoryRegion::incore(unsigned char * result) {
    NORMAL_OP_WRAPPER(mincore(address, length, result));
}

void MemoryRegion::protect(int prot) {
    NORMAL_OP_WRAPPER(mprotect(address, length, prot));
}

void MemoryRegion::protect(int prot, const ProtectionKey &pkey) {
    NORMAL_OP_WRAPPER(pkey_mprotect(address, length, prot, pkey.pkey));
}
