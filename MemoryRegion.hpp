/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Memory operations
 *  
 *  © 2019—2021, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNIXPP_MEMORYREGION_HPP
#define __UNIXPP_MEMORYREGION_HPP

namespace upp {

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
    /** Returns the initial address **/
    void * getAddress() const { return address; }
    /** Returns the length in bytes **/
    size_t getLength() const { return length; }
    
private:
    void * address;
    size_t length;
};

}

#endif
