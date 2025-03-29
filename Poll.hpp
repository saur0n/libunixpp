/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Polling operations
 *  
 *  © 2020—2025, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNIXPP_POLL_HPP
#define __UNIXPP_POLL_HPP

#include <poll.h>
#include <vector>
#include "Stream.hpp"

namespace upp {

class Poll {
public:
    /** There is data to read **/
    static const short IN=POLLIN;
    /** There is some exceptional condition on the file descriptor **/
    static const short PRI=POLLPRI;
    /** Writing is now possible **/
    static const short OUT=POLLOUT;
    /** Stream socket peer closed connection **/
    static const short RDHUP=POLLRDHUP;
    /** Error condition **/
    static const short ERR=POLLERR;
    /** Hang up **/
    static const short HUP=POLLHUP;
    /** Invalid request: fd not open **/
    static const short NVAL=POLLNVAL;
    /**/
    typedef std::vector<struct pollfd>::const_iterator Iterator;
    /**/
    Poll() {}
    /**/
    Poll(const std::vector<Stream> &streams, short events);
    /** Returns number of supervised streams **/
    size_t count() const { return pollfds.size(); }
    /**/
    void add(const Stream &stream, short events);
    /** Wait for events on file descriptors **/
    unsigned poll(int timeout);
    /** Wait for events on file descriptors **/
    unsigned poll(AtomicBool &interrupted, int timeout);
    /** Wait for events on file descriptors, waiting for a signal safely **/
    unsigned poll(const timespec * tmo_p, const sigset_t * sigmask);
    /** Wait for events on file descriptors, waiting for a signal safely **/
    unsigned poll(AtomicBool &interrupted, const timespec * tmo_p, const sigset_t * sigmask);
    /** Returns returned events for the specified stream **/
    short revents(size_t index) const { return pollfds[index].revents; }
    /** Shorthand for revents() **/
    short operator [](size_t index) const { return revents(index); }
    /** Poll just one file descriptor **/
    static short poll(Stream &stream, short events, int timeout);
    /** Poll just one file descriptor **/
    static short poll(AtomicBool &interrupted, Stream &stream, short events, int timeout);
    /** Poll just one file descriptor, waiting for a signal safely **/
    static short poll(Stream &stream, short events, const timespec * tmo_p, const sigset_t * sigmask);
    /** Poll just one file descriptor, waiting for a signal safely **/
    static short poll(AtomicBool &interrupted, Stream &stream, short events, const timespec * tmo_p, const sigset_t * sigmask);
    
private:
    std::vector<struct pollfd> pollfds;
};

}

#endif
