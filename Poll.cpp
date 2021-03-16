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

Poll::Poll(const vector<Stream> &streams, short events) : pollfds(streams.size()) {
    for (size_t i=0; i<streams.size(); i++)
        pollfds[i]={streams[i].fd, events, 0};
}

void Poll::add(const Stream &stream, short events) {
    pollfds.push_back({stream.fd, events, 0});
}

unsigned Poll::poll(int timeout) {
    int result=::poll(pollfds.data(), pollfds.size(), timeout);
    THROW_SYSTEM_ERROR_IF(result<0);
    return unsigned(result);
}
