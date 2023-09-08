/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Event notifier operations
 *  
 *  © 2019—2023, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include "EventNotifier.hpp"
#include "exception.hppi"

using namespace upp;

/******************************************************************************/

EventNotifier::EventNotifier(unsigned int initval, int flags) :
        Stream(eventfd(initval, flags)) {}

eventfd_t EventNotifier::readCounter() {
    eventfd_t result;
    THROW_SYSTEM_ERROR_STD(eventfd_read(getDescriptor(), &result));
    return result;
}

void EventNotifier::writeCounter(eventfd_t off) {
    THROW_SYSTEM_ERROR_STD(eventfd_write(getDescriptor(), off));
}
