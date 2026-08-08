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
    unsigned ioctl(int request) {
        return stream.ioctl(request, nullptr);
    }
    /** Perform an operation on file descriptor **/
    unsigned ioctl(int request, int arg) {
        return stream.ioctl(request, arg);
    }
    /** Get a value using ioctl() **/
    template <class T>
    void get(int request, T &value) const {
        stream.get<T>(request, value);
    }
    /** Set a value using ioctl() **/
    template <class T>
    void set(int request, const T &arg) {
        stream.set<T>(request, arg);
    }
    
private:
    Stream &stream;
};

}

#endif
