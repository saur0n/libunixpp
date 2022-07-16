/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Polling operations
 *  
 *  © 2020—2021, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include "exception.hppi"
#include "Poll.hpp"

using namespace upp;
using std::vector;

static unsigned _poll(pollfd * pollfds, size_t count, int timeout) {
    NORMAL_IO_WRAPPER(int, unsigned, ::poll(pollfds, count, timeout));
}

static unsigned _poll(bool &interrupted, pollfd * pollfds, size_t count, int timeout) {
    INTERRUPTED_IO_WRAPPER(int, unsigned, ::poll(pollfds, count, timeout));
}

static unsigned _poll(pollfd * pollfds, size_t count, const timespec * tmo_p, const sigset_t * sigmask) {
    NORMAL_IO_WRAPPER(int, unsigned, ::ppoll(pollfds, count, tmo_p, sigmask));
}

static unsigned _poll(bool &interrupted, pollfd * pollfds, size_t count, const timespec * tmo_p, const sigset_t * sigmask) {
    INTERRUPTED_IO_WRAPPER(int, unsigned, ::ppoll(pollfds, count, tmo_p, sigmask));
}

Poll::Poll(const vector<Stream> &streams, short events) : pollfds(streams.size()) {
    for (size_t i=0; i<streams.size(); i++)
        pollfds[i]={streams[i].fd, events, 0};
}

void Poll::add(const Stream &stream, short events) {
    pollfds.push_back({stream.fd, events, 0});
}

unsigned Poll::poll(int timeout) {
    return _poll(pollfds.data(), pollfds.size(), timeout);
}

unsigned Poll::poll(bool &interrupted, int timeout) {
    return _poll(interrupted, pollfds.data(), pollfds.size(), timeout);
}

unsigned Poll::poll(const timespec * tmo_p, const sigset_t * sigmask) {
    return _poll(pollfds.data(), pollfds.size(), tmo_p, sigmask);
}

unsigned Poll::poll(bool &interrupted, const timespec * tmo_p, const sigset_t * sigmask) {
    return _poll(interrupted, pollfds.data(), pollfds.size(), tmo_p, sigmask);
}

short Poll::poll(Stream &stream, short events, int timeout) {
    struct pollfd pollfd={stream.fd, events, 0};
    _poll(&pollfd, 1, timeout);
    return pollfd.revents;
}

short Poll::poll(bool &interrupted, Stream &stream, short events, int timeout) {
    struct pollfd pollfd={stream.fd, events, 0};
    _poll(interrupted, &pollfd, 1, timeout);
    return pollfd.revents;
}

short Poll::poll(Stream &stream, short events, const timespec * tmo_p, const sigset_t * sigmask) {
    struct pollfd pollfd={stream.fd, events, 0};
    _poll(&pollfd, 1, tmo_p, sigmask);
    return pollfd.revents;
}

short Poll::poll(bool &interrupted, Stream &stream, short events, const timespec * tmo_p, const sigset_t * sigmask) {
    struct pollfd pollfd={stream.fd, events, 0};
    _poll(interrupted, &pollfd, 1, tmo_p, sigmask);
    return pollfd.revents;
}

