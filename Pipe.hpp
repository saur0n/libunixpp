/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Pipe operations
 *  
 *  © 2019—2020, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNIXPP_PIPE_HPP
#define __UNIXPP_PIPE_HPP

#include <utility>
#include "Stream.hpp"

namespace nx {

/**/
class Pipe : public Stream {
public:
    /** Create a pair of pipes **/
    static std::pair<Pipe, Pipe> create();
    /** Create a pair of pipes **/
    static std::pair<Pipe, Pipe> create(int flags);
    /** Duplicate pipe content **/
    size_t tee(Pipe &out, size_t length, unsigned int flags=0);
    /** Returns pipe capacity **/
    unsigned getCapacity();
    /** Set pipe capacity **/
    void setCapacity(unsigned capacity);
    
private:
    Pipe(int fd);
};

}

#endif
