Name: libunix++
Summary: Object-oriented C++ wrapper around Linux system calls
Version: 0.1
Release: 1
License: LGPLv2
URL: https://saur0n.science/projects/libunix++

%description
Object-oriented C++ wrapper around Linux system calls

%build
make clean
make PLATFORM=SFOS

