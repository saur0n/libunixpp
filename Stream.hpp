#ifndef __RRT_STREAM_HPP
#define __RRT_STREAM_HPP

#include <sys/types.h>
#include <unistd.h>

namespace nx {

/** Base class for all readable-writeable objects **/
class StreamBase {}; // TODO

/** Base class for all descriptor-based objects **/
class Stream {
public:
    /** Duplicate a file descriptor **/
    Stream(const Stream &other);
    /** Duplicate a file descriptor on the specified one **/
    Stream(const Stream &other, int newfd);
    /** Close **/
    virtual ~Stream();
    /** Reposition read//write file offset **/
    off_t seek(off_t offset, int whence=SEEK_SET);
    /** Read from the stream **/
    virtual size_t read(void * buffer, size_t count);
    /** Read from the stream at a given offset **/
    size_t read(void * buffer, size_t count, off_t offset);
    /** Write to the stream **/
    virtual size_t write(const void * buffer, size_t count);
    /** Write to the stream at a given offset **/
    size_t write(const void * buffer, size_t count, off_t offset);
    /** Get file status **/
    void stat(struct stat * statbuf);
    /** Returns file descriptor flags **/
    unsigned getFlags();
    /** Set file descritor flags **/
    void setFlags(unsigned flags);
    
protected:
    /** Initialize by file descriptor **/
    Stream(int fd);
    /** Returns file descriptor **/
    int getDescriptor() const { return fd; }
    /** Perform an operation on file descriptor **/
    unsigned ioctl(int request, void * argp);
    
private:
    int fd;
};

}

#endif
