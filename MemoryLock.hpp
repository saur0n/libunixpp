/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Memory locking operations
 *  
 *  © 2019—2020, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNIXPP_MEMORYLOCK_HPP
#define __UNIXPP_MEMORYLOCK_HPP

#include "MemoryRegion.hpp"
#include <sys/mman.h>

namespace nx {

/**/
class MemoryLock : public MemoryRegion {
public:
    /** Lock an area of memory **/
    MemoryLock(void * addr, size_t length);
    /** Lock an area of memory **/
    MemoryLock(void * addr, size_t length, int flags);
    /** Unlock the area of memory **/
    ~MemoryLock();
    /** Lock all the virtual address space into RAM **/
    static void lockAll(int flags=0);
    /** Unlock all the virtual address space **/
    static void unlockAll();
};

}

#endif
