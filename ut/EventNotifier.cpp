/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Unit tests
 *  
 *  © 2023, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include "unittest.hpp"
#include "../EventNotifier.hpp"

static void run() {
    EventNotifier en(10, EventNotifier::NONBLOCK);
    assert(en.readCounter()==10);
    THROWS(en.readCounter(), EAGAIN);
    en.writeCounter(100);
    assert(en.readCounter()==100);
    THROWS(en.readCounter(), EAGAIN);
}

REGISTER("EventNotifier", run);
