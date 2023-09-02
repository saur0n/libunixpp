/*******************************************************************************
 *  libunix++: C++ wrapper for Linux system calls
 *  Unit tests
 *  
 *  © 2019—2023, Sauron <libunixpp@saur0n.science>
 ******************************************************************************/

#include <iostream>
#include <vector>
#include "unittest.hpp"

using namespace std;

static vector<const UnitTest *> &unitTests() {
    static vector<const UnitTest *> unitTests;
    return unitTests;
}

UnitTest::UnitTest(const char * name, void (* run)()) : name(name), run(run) {
    unitTests().push_back(this);
}

int main(int argc, char ** argv) {
    unsigned count=0;
    
    for (auto i=unitTests().begin(); i!=unitTests().end(); ++i) {
        const UnitTest * unitTest=*i;
        cout << "[" << unitTest->name << "]\n";
        unitTest->run();
        count++;
    }
    
    cout << "Successfully executed " << count << " unit tests." << endl;
    
    return 0;
}
