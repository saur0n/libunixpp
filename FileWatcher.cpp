/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  inotify wrapper
 *  
 *  © 2026, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include "exception.hppi"
#include "FileWatcher.hpp"

using namespace upp;

/******************************************************************************/

FileWatcher::FileWatcher() : Stream(inotify_init()) {}

FileWatcher::FileWatcher(int flags) : Stream(inotify_init1(flags)) {}

unsigned FileWatcher::add(const char * path, uint32_t mask) {
    NORMAL_FN_WRAPPER(inotify_add_watch(getDescriptor(), path, mask));
}

void FileWatcher::remove(unsigned wd) {
    NORMAL_OP_WRAPPER(inotify_rm_watch(getDescriptor(), wd));
}
