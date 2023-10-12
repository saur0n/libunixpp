################################################################################
#   libunix++: C++ wrapper for Linux system calls
#   Build rules
#   
#   © 2019—2023, Sauron
################################################################################

NAME=unix++
CC=$(if $(TOOLCHAIN), /usr/bin/$(TOOLCHAIN)-)gcc
CXX=$(if $(TOOLCHAIN), /usr/bin/$(TOOLCHAIN)-)g++
INCLUDEDIR=$(if $(TOOLCHAIN), /usr/$(TOOLCHAIN)/libc/usr/include, /usr/include)
CFLAGS=-fPIC -Os -Wall -Wextra -Wno-unused-parameter
CXXFLAGS=$(CFLAGS)
LIBRARIES=-lrt -lstdc++
SOURCES=*.cpp
HEADERS=*.hpp
OUTPUT=lib$(NAME).so
PLATFORM?=STD

all: $(OUTPUT)

compat.o: compat.c
	$(CC) -c $(CFLAGS) -DPLATFORM_$(PLATFORM) -o $@ compat.c

$(OUTPUT): $(SOURCES) $(HEADERS) compat.o
	$(CXX) -shared $(CXXFLAGS) -DPLATFORM_$(PLATFORM) -o $@ $(SOURCES) compat.o $(LIBRARIES)

unittest: $(SOURCES) $(HEADERS) ut/*.cpp ut/*.hpp
	$(CXX) -g $(CXXFLAGS) -DPLATFORM_$(PLATFORM) -o $@ $(SOURCES) ut/*.cpp $(LIBRARIES)

clean:
	rm -f *.o *.so unittest

release: all
	strip $(OUTPUT)

install: all
	install -s $(OUTPUT) /usr/lib64
	mkdir -p $(INCLUDEDIR)/$(NAME)
	cp $(HEADERS) $(INCLUDEDIR)/$(NAME)

test: unittest
	./unittest

.PHONY:
	all release install clean test
