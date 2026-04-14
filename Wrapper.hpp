#ifndef __UNIXPP_WRAPPER_HPP
#define __UNIXPP_WRAPPER_HPP

#include "Stream.hpp"

namespace upp {

/** Base class for stream wrappers **/
class Wrapper {
public:
    /** Wrap the already opened stream **/
    explicit Wrapper(Stream &stream);
    /** Wrap the standard stream **/
    explicit Wrapper(Stream::Standard no);
    /** Returns the underlying stream **/
    Stream &getStream() const { return stream; }
    /** Access the underlying stream **/
    Stream &operator *() const { return stream; }
    /** Access the underlying stream **/
    Stream * operator ->() const { return &stream; }
    /** Returns file descriptor **/
    int getDescriptor() const;
    
protected:
    /** Perform an operation on file descriptor **/
    unsigned ioctl(int request);
    /** Perform an operation on file descriptor **/
    unsigned ioctl(int request, void * argp) const;
    /** Perform an operation on file descriptor **/
    unsigned ioctl(int request, const void * argp);
    /** Perform an operation on file descriptor **/
    unsigned ioctl(int request, int argp);
    
private:
    Stream &stream;
};

}

#endif
