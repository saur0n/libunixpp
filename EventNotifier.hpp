/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Event notifier operations
 *  
 *  © 2019—2023, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNIXPP_EVENTNOTIFIER_HPP
#define __UNIXPP_EVENTNOTIFIER_HPP

#include <sys/eventfd.h>
#include "Stream.hpp"

namespace upp {

/** File descriptor for event notification **/
class EventNotifier : public Stream {
public:
    /** Set the close-on-exec flag on a new file descriptor **/
    static const int CLOEXEC=EFD_CLOEXEC;
    /**/
    static const int NONBLOCK=EFD_NONBLOCK;
    /** Provide semaphore-like semantics for reads **/
    static const int SEMAPHORE=EFD_SEMAPHORE;
    /** Create file descriptor for event notification **/
    EventNotifier(unsigned int initval, int flags);
    /** Return the counter value **/
    eventfd_t readCounter();
    /** Add to the counter value **/
    void writeCounter(eventfd_t off);
};

}

#endif
