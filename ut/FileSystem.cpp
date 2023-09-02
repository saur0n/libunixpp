/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Unit tests
 *  
 *  © 2019—2023, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include <cstring>
#include "../File.hpp"
#include "unittest.hpp"

static const char * TEST_FILE="./rogue.tmp";

static mode_t getPermissions(const char * pathname) {
    struct stat sb;
    int retval=::stat(pathname, &sb);
    return retval<0?0:sb.st_mode&07777;
}

static void createFile(const char * pathname) {
    File file(pathname, O_CREAT|O_WRONLY|O_TRUNC);
}

static void run() {
    createFile(TEST_FILE);
    createFile("/tmp/rogue-3.tmp");
    
    // access()
    assert(FileSystem::access(TEST_FILE, F_OK));
    assert(FileSystem::access(TEST_FILE, R_OK));
    assert(FileSystem::access(TEST_FILE, W_OK));
    assert(FileSystem::access("/proc/version", F_OK));
    assert(FileSystem::access("/proc/version", R_OK));
    assert(FileSystem::access("/proc/version", W_OK)==false);
    assert(FileSystem::access("/proc/sauron", F_OK)==false);
    THROWS(FileSystem::access("/proc/sauron", R_OK), ENOENT);
    THROWS(FileSystem::access("/proc/sauron", W_OK), ENOENT);
    
    // chmod()
    FileSystem::chmod(TEST_FILE, 0604);
    assert(getPermissions(TEST_FILE)==0604);
    FileSystem::chmod(TEST_FILE, 0660);
    assert(getPermissions(TEST_FILE)==0660);
    THROWS(FileSystem::chmod("/proc/version", 0777), EPERM);
    THROWS(FileSystem::chmod("/nonexistent", 0777), ENOENT);
    
    // chown(): not tested because root permissions are needed
    
    // lchown(): not tested because root permissions are needed
    
    // link()
    File lfile("/tmp/rogue.linked", O_CREAT|O_WRONLY|O_TRUNC);
    ::unlink("/tmp/rogue-2.tmp");
    FileSystem::link("/tmp/rogue.linked", "/tmp/rogue-2.tmp");
    assert(FileSystem::access("/tmp/rogue-2.tmp", F_OK));
    THROWS(FileSystem::link(TEST_FILE, "/proc/version"), EEXIST);
    
    // lstat()
    if (false==FileSystem::access("/tmp/rogue-7.tmp"))
        FileSystem::symlink(TEST_FILE, "/tmp/rogue-7.tmp");
    struct stat lsbuf;
    FileSystem::lstat("/tmp/rogue-7.tmp", &lsbuf);
    assert(S_ISLNK(lsbuf.st_mode));
    lsbuf=FileSystem::lstat("/tmp/rogue-7.tmp");
    THROWS(FileSystem::lstat("/nonexistent"), ENOENT);
    
    // mkdir()
    ::rmdir("/tmp/rogue-4.tmp");
    FileSystem::mkdir("/tmp/rogue-4.tmp");
    assert(FileSystem::access("/tmp/rogue-4.tmp", F_OK));
    THROWS(FileSystem::mkdir("/nonexistent/a", 0700), ENOENT);
    ::rmdir("/tmp/rogue-4.tmp");
    FileSystem::mkdirp("/tmp/rogue-4.tmp");
    assert(FileSystem::access("/tmp/rogue-4.tmp", F_OK));
    FileSystem::mkdirp("/tmp/rogue-4.tmp"); // already exists
    THROWS(FileSystem::mkdirp("/nonexistent/a", 0700), ENOENT);
    
    // mknod()
    ::unlink("/tmp/rogue-x.tmp");
    FileSystem::mknod("/tmp/rogue-x.tmp", S_IFIFO|0700, 0);
    assert(FileSystem::access("/tmp/rogue-x.tmp", F_OK));
    THROWS(FileSystem::mknod("/nonexistent/a", S_IFIFO|0700, 0), ENOENT);
    
    // readlink()
    
    // rename()
    ::unlink("/tmp/rogue-5.tmp");
    ::unlink("/tmp/rogue-6.tmp");
    FileSystem::link("/tmp/rogue.linked", "/tmp/rogue-5.tmp");
    FileSystem::rename("/tmp/rogue-5.tmp", "/tmp/rogue-6.tmp");
    assert(FileSystem::access("/tmp/rogue-5.tmp")==false);
    assert(FileSystem::access("/tmp/rogue-6.tmp")==true);
    THROWS(FileSystem::rename("/nonexistent", "/nonexistent2"), ENOENT);
    
    // rmdir()
    FileSystem::rmdir("/tmp/rogue-4.tmp");
    assert(!FileSystem::access("/tmp/rogue-4.tmp", F_OK));
    THROWS(FileSystem::rmdir("/nonexistent"), ENOENT);
    
    // stat()
    struct stat sbuf;
    FileSystem::stat(TEST_FILE, &sbuf);
    assert(sbuf.st_ino!=0);
    THROWS(FileSystem::stat("/nonexistent", &sbuf), ENOENT);
    THROWS(FileSystem::stat(TEST_FILE, nullptr), EFAULT);
    
    // statfs()
    FileSystem::StatFS sf;
    FileSystem::statfs("/", sf);
    assert(sf.f_type!=0);
    FileSystem::StatFS sfProc=FileSystem::statfs("/proc");
    assert(sfProc.f_type==0x9FA0);
    
    // symlink()
    ::unlink("/tmp/rogue-3.tmp");
    FileSystem::symlink(TEST_FILE, "/tmp/rogue-3.tmp");
    assert(FileSystem::access("/tmp/rogue-3.tmp", F_OK));
    THROWS(FileSystem::symlink(TEST_FILE, "/proc/version"), EEXIST);
    THROWS(FileSystem::symlink("/nonexistent", "/nonexistent2"), EACCES);
    
    // sync()
    FileSystem::sync();
    
    // truncate()
    FileSystem::truncate(TEST_FILE, 20);
    THROWS(FileSystem::truncate("/proc/version", 20), EACCES);
    THROWS(FileSystem::truncate("/nonexistent", 30000), ENOENT);
    
    // unlink()
    FileSystem::unlink("/tmp/rogue-3.tmp");
    assert(!FileSystem::access("/tmp-rogue-3", F_OK));
    THROWS(FileSystem::unlink("/proc/version"), EACCES);
    THROWS(FileSystem::unlink("/nonexistent"), ENOENT);
    
    // utimes()
    const struct timeval newtime[]={{1337, 0}, {1338, 0}};
    FileSystem::utimes(TEST_FILE, newtime);
    struct stat sbuf2;
    FileSystem::stat(TEST_FILE, &sbuf2);
    assert(sbuf2.st_atim.tv_sec==1337);
    assert(sbuf2.st_mtim.tv_sec==1338);
    
    // setAttribute()
    FileSystem::setAttribute(TEST_FILE, "user.color", "#9F5044", 7UL);
    THROWS(FileSystem::setAttribute(TEST_FILE, "unsupported.z", "1", 1UL), ENOTSUP);
    THROWS(FileSystem::setAttribute("/proc/version", "user.z", "1", 1UL), EACCES);
    
    // getAttribute()
    char xattrvalue[32];
    assert(FileSystem::getAttribute(TEST_FILE, "user.color", xattrvalue, 32UL)==7UL);
    assert(0==strcmp(xattrvalue, "#9F5044"));
    THROWS(FileSystem::getAttribute(TEST_FILE, "unsupported.z", xattrvalue, 32UL), ENOTSUP);
    THROWS(FileSystem::setAttribute("/proc/version", "user.z", xattrvalue, 32UL), EACCES);
    
    // listAttributes()
    
    // removeAttribute()
    FileSystem::removeAttribute(TEST_FILE, "user.color");
    THROWS(FileSystem::removeAttribute(TEST_FILE, "user.nonexistent"), ENODATA);
    THROWS(FileSystem::removeAttribute("/nonexistent", "user.color"), ENOENT);
    THROWS(FileSystem::removeAttribute("/proc/version", "user.z"), EACCES);
    
    // chdir()
    FileSystem::chdir("/usr");
    THROWS(FileSystem::chdir("/nonexistent"), ENOENT);
    
    // getcwd()
    assert(FileSystem::getcwd()=="/usr");
}

REGISTER("FileSystem", run);
