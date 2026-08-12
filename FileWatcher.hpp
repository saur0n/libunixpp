/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  inotify wrapper
 *  
 *  © 2026, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNIXPP_FILEWATCHER_HPP
#define __UNIXPP_FILEWATCHER_HPP

#include <sys/inotify.h>
#include "Stream.hpp"

namespace upp {

/** Inotify wrapper **/
class FileWatcher : public Stream {
public:
    /** Flags **/
    enum Flags {
        /** Set flag O_CLOEXEC for newly opened file descriptor **/
        CLOEXEC=IN_CLOEXEC,
        /** Set flag O_NONBLOCK for newly opened file descriptor **/
        NONBLOCK=IN_NONBLOCK
    };
    /** Possible input and output event types **/
    enum Events {
        /** File was accessed. **/
        ACCESS=IN_ACCESS,
        /** File was modified. **/
        MODIFY=IN_MODIFY,
        /** Metadata changed. **/
        ATTRIB=IN_ATTRIB,
        /** Writtable file was closed. **/
        CLOSE_WRITE=IN_CLOSE_WRITE,
        /** Unwrittable file closed. **/
        CLOSE_NOWRITE=IN_CLOSE_NOWRITE,
        /** File was opened. **/
        OPEN=IN_OPEN,
        /** File was moved from X. **/
        MOVED_FROM=IN_MOVED_FROM,
        /** File was moved to Y. **/
        MOVED_TO=IN_MOVED_TO,
        /** Subfile was created. **/
        CREATE=IN_CREATE,
        /** Subfile was deleted. **/
        DELETE=IN_DELETE,
        /** Self was deleted. **/
        DELETE_SELF=IN_DELETE_SELF,
        /** Self was moved. **/
        MOVE_SELF=IN_MOVE_SELF,
        /** Backing fs was unmounted. **/
        UNMOUNT=IN_UNMOUNT,
        /** Event queued overflowed. **/
        Q_OVERFLOW=IN_Q_OVERFLOW,
        /** File was ignored. **/
        IGNORED=IN_IGNORED,
        /** Only watch the path if it is a directory. **/
        ONLYDIR=IN_ONLYDIR,
        /** Do not follow a sym link. **/
        DONT_FOLLOW=IN_DONT_FOLLOW,
        /** Exclude events on unlinked objects. **/
        EXCL_UNLINK=IN_EXCL_UNLINK,
        /** Only create watches. **/
        MASK_CREATE=IN_MASK_CREATE,
        /** Add to the mask of an already existing watch. **/
        MASK_ADD=IN_MASK_ADD,
        /** Event occurred against dir. **/
        ISDIR=IN_ISDIR,
        /** Only send event once. **/
        ONESHOT=IN_ONESHOT,
    };
    /** Structure describing an inotify event **/
    using Event=::inotify_event;
    /** Initialize a file watcher **/
    FileWatcher();
    /** Initialize a file watcher with flags **/
    explicit FileWatcher(int flags);
    /** Add a new watch, or modify an existing watch **/
    unsigned add(const char * path, uint32_t mask);
    /** Remove the watch **/
    void remove(unsigned wd);
};

}

#endif
