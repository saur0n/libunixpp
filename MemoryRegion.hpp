/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Memory operations
 *  
 *  © 2019—2025, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNIXPP_MEMORYREGION_HPP
#define __UNIXPP_MEMORYREGION_HPP

#include <sys/mman.h>

namespace upp {

/**/
class ProtectionKey {
    friend class MemoryRegion;
public:
    /**/
    static const int DISABLE_ACCESS;
    /**/
    static const int DISABLE_WRITE;
    /** Allocate a protection key **/
    explicit ProtectionKey(unsigned int accessRights);
    /** Allocate a protection key **/
    ProtectionKey(unsigned int flags, unsigned int accessRights);
    /** Free the protection key **/
    ~ProtectionKey();
    
private:
    ProtectionKey(const ProtectionKey &other)=delete;
    ProtectionKey &operator =(const ProtectionKey &other)=delete;
    
    int pkey;
};

/** A contiguous region of memory **/
class MemoryRegion {
public:
    /** Create a memory region with defined start address and length **/
    MemoryRegion(void * address, size_t length);
    /** Give advice about use of memory **/
    void advise(int advise);
    /** Determine whether pages are resident in memory **/
    void incore(unsigned char * result);
    /** Set protection on a region of memory **/
    void protect(int prot);
    /** Set protection on a region of memory **/
    void protect(int prot, const ProtectionKey &pkey);
    /** Returns the initial address **/
    void * getAddress() const { return address; }
    /** Returns the length in bytes **/
    size_t getLength() const { return length; }
    
protected:
    void * address;
    size_t length;
};

}

#endif
