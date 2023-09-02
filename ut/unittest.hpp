/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Unit tests
 *  
 *  © 2019—2023, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#ifndef __UNITTEST_HPP
#define __UNITTEST_HPP

#include <cassert>
#include <system_error>
#include "../FileSystem.hpp"

using namespace upp;

struct UnitTest {
    /** Register an unit test in the registry **/
    explicit UnitTest(const char * name, void (* run)());
    const char * name;
    void (* run)();
};

#define THROWS(statement, expected) \
    try { \
        statement; \
    } \
    catch (const std::system_error &se) { \
        auto &code=se.code(); \
        if ((code.category()!=std::system_category())||(code.value()!=expected)) \
            throw; \
    }
#define REGISTER(name, run) \
    static UnitTest __UT(name, run);

#endif
