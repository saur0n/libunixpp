################################################################################
#   libunix++: C++ wrapper for Linux system calls
#   Build file for examples
#   
#   © 2020, Sauron <libunixpp@saur0n.science>
################################################################################

CXXFLAGS=-Wall -Wextra -Os
LIBRARIES=-lstdc++ -lunix++

all: ls resolve sdelete

clean:
	rm -f ls resolve sdelete

ls: ls.cpp
	gcc $(CXXFLAGS) -o $@ $(LIBRARIES) $<

resolve: resolve.cpp
	gcc $(CXXFLAGS) -o $@ $(LIBRARIES) $<

sdelete: sdelete.cpp
	gcc $(CXXFLAGS) -o $@ $(LIBRARIES) $<

.PHONY: all clean
