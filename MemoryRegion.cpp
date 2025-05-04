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

#ifdef PLATFORM_MUSL
int pkey_alloc(unsigned int flags, unsigned int access_rights) {
    throw std::system_error(ENOSYS, std::system_category());
}

int pkey_free(int pkey) {
    throw std::system_error(ENOSYS, std::system_category());
}

int pkey_mprotect(void * addr, size_t size, int prot, int pkey) {
    throw std::system_error(ENOSYS, std::system_category());
}
#endif

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
