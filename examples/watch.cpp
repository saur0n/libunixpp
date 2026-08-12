/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Example: file alteration monitor
 *  
 *  © 2026, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include <iostream>
#include <map>
#include <unix++/FileWatcher.hpp>

using std::cerr;
using std::cout;
using std::endl;
using std::map;
using upp::FileWatcher;

int main(int argc, char ** argv) {
    try {
        FileWatcher fileWatcher;
        map<unsigned, const char *> watches;
        
        for (int i=1; i<argc; i++) {
            unsigned wd=fileWatcher.add(argv[i], FileWatcher::MODIFY|FileWatcher::ATTRIB);
            watches.try_emplace(wd, argv[i]);
        }
        
        for (;;) {
            char buffer[4096];
            size_t n=fileWatcher.read(buffer, sizeof(buffer));
            for (FileWatcher::Iterator ei(buffer, n); ei; ++ei) {
                cout << watches[ei->wd] << ": ";
                if (ei->mask&FileWatcher::MODIFY)
                    cout << "modified ";
                if (ei->mask&FileWatcher::ATTRIB)
                    cout << "attributes changed ";
                cout << "\n";
            }
        }
        
        return 0;
    }
    catch (const std::exception &e) {
        cerr << argv[0] << ": " << e.what() << endl;
        return 1;
    }
}
