/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Atomic bool type
 *  
 *  © 2025, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNIXPP_ATOMICBOOL_HPP
#define __UNIXPP_ATOMICBOOL_HPP

#include <atomic>

namespace upp {

/** Interrupted flag **/
using AtomicBool=std::atomic<bool>;

}

#endif
