/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  ...
 *  
 *  © 2019—2020, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNIXPP_STREAM_HPP
#define __UNIXPP_STREAM_HPP

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
    /** Duplicate a file descriptor on the specified one **/
    Stream(const Stream &other, int newfd, int flags);
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
    /** Returns file status flags **/
    unsigned getStatusFlags();
    /** Set file status flags **/
    void setStatusFlags(unsigned flags);
    /** Returns ID of process receiving signals about events on the descriptor **/
    int getOwner();
    /** Write a file into the file descriptor **/
    size_t sendfile(Stream &from, size_t count);
    /** Write a file into the file descriptor **/
    size_t sendfile(Stream &from, off_t &offset, size_t count);
    
protected:
    /** Initialize by file descriptor **/
    Stream(int fd);
    /** Returns file descriptor **/
    int getDescriptor() const { return fd; }
    /** Perform an operation on file descriptor **/
    unsigned ioctl(int request, void * argp);
    /** Manipulate file descriptor **/
    unsigned fcntl(int cmd);
    /** Manipulate file descriptor **/
    unsigned fcntl(int cmd, int arg);
    
private:
    int fd;
};

}

#endif
